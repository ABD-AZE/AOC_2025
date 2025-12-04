#include <iostream>
#include <string> 
#include <fstream>
#include <vector>
#include <ranges>
#include <print>
#include <algorithm>
#include <numeric>

int main(){
    std::ifstream file("input.txt");
    std::vector<std::string> input;
    if(file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            input.push_back(line);
        }
        file.close();
    }
    input.insert(input.begin(), std::string(input[0].size(), '.'));
    input.push_back(std::string(input[0].size(), '.'));
    auto transformed = input | std::views::transform([](const auto& line){
        return std::string(".") + line + ".";
    });
    input = std::vector<std::string>(transformed.begin(), transformed.end());
    auto ans = [&](){
        return std::ranges::distance(input | std::views::enumerate | std::views::transform([&input](const auto&& indexed_line){
            const auto& [i, line] = indexed_line;
            return line | std::views::enumerate | std::views::transform([&input, i](const auto&& indexed_char){
                const auto& [j, ch] = indexed_char;
                return ch == '@' ? [&input, i, j]() -> int {
                    auto directions = std::views::cartesian_product(
                        std::views::iota(-1, 2),
                        std::views::iota(-1, 2)
                    ) | std::views::filter([](const auto& p) { 
                        auto [di, dj] = p; 
                        return !(di == 0 && dj == 0); 
                    });
                    
                    return std::ranges::count_if(directions, [&input, i, j](const auto& p) {
                        auto [di, dj] = p;
                        return input[i + di][j + dj] == '@';
                    }) < 4;
                }() : 0;
            });
        }) | std::views::join | std::views::filter([](int val){ return val == 1; }));
    };
    std::println("Answer: {}", ans());
    return 0;
}