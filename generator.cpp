#include <cstddef>   // std::size_t
#include <iostream>  // std::cout

template <std::size_t A, std::size_t... B>
struct generator;

template<std::size_t A>
struct generator<A>;

template<std::size_t a, std::size_t... B>
auto make_generator() {
    auto x = generator<a, B...>{};
    return x;
}

template <std::size_t A, std::size_t... B>
struct generator {
    int global_count = 0;
    int original = 0;

    decltype(A) first = A;
    generator<B...> rest = make_generator<B...>();

    auto at(int i);

    auto assign(int i, std::size_t x);

    auto output_until(int x);
};

template<std::size_t A, std::size_t... B>
auto generator<A>::output_until(int x)
{
    if(x == global_count)
    {
        return 0;
    }
    std::cout << first;
    global_count++;
    auto y = make_generator(B...);
    y.output_until(x);
}

template <std::size_t A>
struct generator<A> {
    int global_count = 0;
    int original = 0;

    decltype(A) first = A;

    auto at(int i);

    auto assign(int i, std::size_t x);

    auto output_until(int x);
};

template<std::size_t A>
auto generator<A>::output_until(int x)
{
    std::cout << first;
    global_count++;
}

template <std::size_t A, std::size_t... B>
auto generator<A, B...>::at(int i) {
    if (global_count == 0) {
        original = i;
    }
    if (global_count == original) {
        std::cout << A;
        global_count = 0; original = 0;
        return A;
    }
    global_count++;
    auto z = make_generator<B...>();
    return z.at(i - 1);
}

template <std::size_t A, std::size_t... B>
auto generator<A, B...>::assign(int i, std::size_t x) {
    if (global_count == 0) {
        original = i;
    }
    if (global_count == original) {
        std::cout << A;
        // A = x;
        // constexpr auto xyz = const_cast<decltype(x)const>(x);
        const std::size_t m = const_cast<std::size_t&>(x);
        auto y = generator<m, B...>{};
        global_count = 0; original = 0;
        return y;
    }
    global_count++;
    auto z = make_generator<B...>();
    return z.at(i - 1);
}


template <std::size_t A>
auto generator<A>::at(int i) {
    if (i == original) {
        std::cout << A;
        global_count = 0; original = 0;
        return A;
    } else {
        std::cout << "The int i variable was too large.\n";
        return -1lu;  // -1 long unsigned int
    }
}

template <std::size_t A>
auto generator<A>::assign(int i, std::size_t x) {
    if (i == original) {
        std::cout << A;
        A = x;
        global_count = 0; original = 0;
        return *this;
    } else {
        std::cout << "The int i variable was too large.\n";
        return -1lu;  // -1 long unsigned int
    }
}

template <auto A, auto... B>
auto inc(generator<A, B...> x, int y) {
    auto xyz = x.at(y);
    if (xyz == 255) {
        xyz = 0;
        return xyz;
    } else {
        return xyz + 1;
    }
    x.output_until(y);
    return xyz;
}

int main() {  //                            10 11 12 13
    //       (0)(1)(2)(3)(4)(5)(6)(7)(8)(9) ()()  () () ()()()(18)()()()()
    std::cout << "Finding element in generator at index 4: \t";
    generator<2, 4, 6, 7, 4, 2, 5, 2, 6, 2, 9, 5, 1, 2, 6, 52, 32, 58, 34, 255> x{};
    auto y = inc(x, 4);
    std::cout << "\nIncremented is:                          \t" << y << "\n";
    x.assign(2, 4);

    return 0;
}
