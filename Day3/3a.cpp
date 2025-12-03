#include <iostream>
#include <string>
#include <fstream>
#include <ranges>
#include <string_view>
#include <numeric>
#include <vector>
#include <algorithm>
#include <print>

using namespace std;

int main(){
    std::ifstream in("input.txt");
    std::string s;
    
    s.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    auto lines = s | std::views::split('\n');
    auto view = s | std::views::split('\n') | std::views::transform([](auto&& rng){
        auto pairs = rng | std::views::enumerate | std::views::transform([](auto&& pair) -> std::pair<int, int> {
            const auto& [index, c] = pair;
            return {c - '0', index};
        });
        std::vector<std::pair<int, int>> vec(pairs.begin(), pairs.end());
        std::ranges::sort(vec, [](const auto& a, const auto& b) { return a.first == b.first ? a.second > b.second : a.first < b.first; });
        std::ranges::reverse(vec);
        auto next_largest = vec | std::views::filter([&](const auto& p){
            return p.second > vec[0].second;
        }) | std::views::take(1);
        return next_largest.empty() ? vec[1].first*10 + vec[0].first : vec[0].first*10 + (*next_largest.begin()).first; 
    });
    const auto ans = std::accumulate(view.begin(), view.end(), 0L, std::plus<>());
    std::println("Answer: {}", ans);
    return 0;
}