// #include<https://raw.githubusercontent.com/robertshepherdcpp/files/main/formt.cpp>
// formt::format
#include <any>              // std::any
#include <functional>       // std::bind_back
#include <iomanip>          // std::boolalpha
#include <iostream>         // std::cout
#include <numbers>          // std::numbers::pi_v c++20
#include <ranges>           // std::ranges
#include <source_location>  // std::source_location
#include <string>           // std::string, std::string_view
#include <typeinfo>         // std::type_info
#include <vector>           // std::vector

[[nodiscard(
    "Don’t call this heavy function if you don’t need the result!")]] bool
Compute() {
    return true;
}

void log(const std::string_view& message, const std::source_location& location =
                                              std::source_location::current()) {
    std::cout << "|     File|line|        |Function Name|Message|\n";
    std::cout << "info:" << location.file_name() << ":" << location.line()
              << " " << location.function_name() << " " << message << '\n';
}

template <typename T>
struct types {
    using type = T;
    using reference = T&;
    using pointer = T*;
    using rvalueref = T&&;
    using pointertopointer = T**;
    using vector = std::vector<T>;
};

auto print(auto&& vec) {
    for (int x = 0; auto&& i : vec) {
        std::cout << x << " " << std::move(i) << "\n";
        x++;
    }
}

auto func(int a, int b, int c, int d) {
    std::cout << "func: " << a << ' ' << b << ' ' << c << ' ' << d << "\n";
}

int count = 0;

template <auto t, auto... ts>
struct container {
    int count__ = 0;
    /* static constexpr */ decltype(t) data_e = t;
    /* static constexpr */ container<ts...> data_e_rest = make_container(ts...);

    auto size();  // have to find size of parameter pack
};

template <typename T, typename... Ts>
auto size_helper(T t, Ts... ts) {
    count++;
    size_helper(ts...);
}

template <typename T>
auto size_helper(T t) {
    count++;
}

template <typename... T>
auto size_helper(int& count_, T... ts) {
    count_++;
    count = count_;
    size_helper(ts...);
}

template <auto t, auto... ts>
auto container<t, ts...>::size() {
    count__++;
    size_helper(count__, ts...);
    return count;
    count = 0;
}

template <auto T>
concept has_size_member = T
.size() != -1;

template <typename T, typename B>
struct type_with_two_types {
    T fist_type{};
    B second_type{};
};

auto assume(bool b, const std::source_location& location =
                        std::source_location::current()) {
    if (!b) {
        std::cout << "The function: " << location.function_name() << " assumed."
                  << "/nAnd you violated the the assumption";
    }
}

auto half(auto range)
    -> type_with_two_types<decltype(range),
                           decltype(range)>  // passing by rvalue ref
{
    assume(range.size() == 0);  // doesnt really do much. Debugging purposes.
    auto size = range.size();

    auto half_way = size / 2;
    decltype(range) r = range;
    for (int i = 0; i < half_way; i++) {
        r[i] = range[i];
    }
    decltype(range) w = range;
    for (int i = half_way; i < range.size(); i++) {
        w[i] = range[i];
    }

    type_with_two_types<decltype(range), decltype(range)> twtt{r, w};

    return twtt;
}

int main() {
    // formt::format("{}", std::type_info(types<int>::type));
    // auto x = std::type_info(types<int>::type).name();

    // formt::format("Hello {}", 42);

    std::cout << std::boolalpha;

    std::cout << std::numbers::pi_v<double>;
    std::vector vec{1, 2, 3, 4, 5,
                    6, 7, 8, 9, 10};  // dont need to specify type: CTAD.
    std::cout << "\n";
    for (int i = 0;
         auto& x :
         vec)  // the new c++20 way can have a variable declaration in for loop
    {
        std::cout << "At element " << i << ": " << x << "\n";
    }
    auto x{vec | std::ranges::views::filter([](int i) { return i % 2 == 0; }) |
           std::ranges::views::transform([](int i) { return i * 4; })};
    //| std::ranges::views::reverse(vec)};
    print(x);

    log("Hello World.");
    log("World.");

    std::cout << "\nExample Bind Front Implementation:"
              << "\n";

    auto f = std::bind_front(func, 42, 84);

    f(16, 24);  // c++20 feature. std::bind_back coming in c++23.

    std::any xyz = 42;
    // std::cout << "Currently any is: " << xyz << "\n";
    int h = std::any_cast<int>(xyz);
    std::cout << "Currently any is: " << h << "\n";

    xyz = true;
    bool s = std::any_cast<bool>(xyz);
    std::cout << "Now any is: " << s << "\n";

    xyz = 'C';
    char c = std::any_cast<char>(xyz);
    std::cout << "Now any is: " << c << "\n";

    // container<1, 2, 3, 4> c;
    std::vector<std::string_view> v{"Hello C++", "std::ranges", "std::chrono",
                                    "std::views",
                                    "[](){std::cout << \"Lambda\"}"};
    auto simon = half(v);
    print(simon.fist_type);
    std::cout << "The second half of the vector is:\n";
    print(simon.second_type);
}
