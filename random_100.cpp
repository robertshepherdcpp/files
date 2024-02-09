#include<iostream>
#include<random>
#include<map>
#include<ranges>

auto random_number() -> int
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

    return dist6(rng);
}

int main()
{
    std::map<int, int> count{};
    for(int i : std::ranges::views::iota(0) | std::ranges::views::take(100))
    {
        count[random_number()]++;
    }
    for(const auto [a, b] : count)
    {
        std::cout << a << ": " << b << "\n";
    }
}
