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

int main()
{
    std::ifstream in("input.txt");
    std::string s;

    s.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    auto view = s | std::views::split('\n') | std::views::transform([](auto &&rng)
                                                                    {
        std::vector<char> vec(rng.begin(), rng.end());
        std::vector<char> max_joltage(12);
        int begin = 0;
        for (auto&& [index, element] : std::views::enumerate(max_joltage)) {
            element = [&](int& begin,int end) -> char{
            return *(vec.begin() + (begin = std::max_element(vec.begin() + begin, vec.end() - end) - vec.begin() + 1)-1);
        }(begin, 11 - index);
        }
        return stol(std::string(max_joltage.begin(), max_joltage.end())); });
    const auto ans = std::accumulate(view.begin(), view.end(), 0L, std::plus<>());
    std::println("Answer: {}", ans);
    return 0;
}