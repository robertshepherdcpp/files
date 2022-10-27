#include <iostream> // std::cout
#include <string> // std::string

template <typename... Args>
auto sum(Args... args) {
    return (... + args);  // c++17 fold
}

template <typename Arg, typename... Args>
auto summ(Arg a, Args... as) {
    return a + sum(as...);
}

template <typename Arg>
auto summ(Arg a) {
    return a;
}

// some
template <typename T>
auto some(T t) -> T {
    return t;
}

template <typename B, typename T, typename... Ts>
auto some(T t, Ts... ts) {
    return B(t, ts...);
}

template <typename T, typename... Ts>
struct tuple;

template <typename T>
struct tuple<T>;

template <typename T, typename... Ts>
auto make_tuple(T t, Ts... ts) {
    return tuple(t, ts...);
}

template <typename T, typename... Ts>
struct tuple {
    T first = T{};
    tuple<Ts...> rest;

    tuple(T t, Ts... ts) {
        first = t;
        rest = make_tuple(ts...);
    }

    tuple(){};

    tuple(T t) { first = t; }
};

template <typename T>
struct tuple<T> {
    T first = T{};

    tuple(T t) { first = t; }
};

template <typename T>
struct crtp {
    auto operator++(int t) { t++; }

    int i;
};

struct crtp_a : crtp<crtp_a> {
    int y;
};

struct crtp_b : crtp<crtp_b> {
    int y;
};

struct PHINode {};

auto assert(bool b, std::string s) {}

struct Register {
    auto isVirtualRegister(Register r) { return true; }

    auto operator==(Register r) { return 1; }

    auto operator!() { return false; }

    std::string_view xyz = "Hello";
};

struct x {
    auto grow(Register r) {r.xyz = "...";}
};

x LiveOutRegInfo;

template <typename T, typename B>
struct pair {
    T first;
    B second;
};

namespace Reg {
auto isVirtualRegister(Register DestReg) { return true; }
}  // namespace Reg

Register a, b;

pair<Register, Register> It{a, b};

void ComputePHILiveOutRegInfo(const PHINode *PN) {
    // ....
    Register DestReg = It.second;
    if (!DestReg)
        return assert(Reg::isVirtualRegister(DestReg),
                      "Expected a virtual reg");
    LiveOutRegInfo.grow(DestReg);
    // ....
}

struct metres
{
    metres(long double x)
    {
        metres_ = x;
    }

    double metres_;
};

namespace literals
{
auto operator""_m(long double x)
{
    return metres(x);
}

auto operator""_km(long double x)
{
    return metres(x * 1000);
}

auto operator""_cm(long double x)
{
    return metres(x / 100);
}
}

int main() {
    std::cout << "Sum of sum(1, 5, 10, 15, 20): " << sum(1, 5, 10, 15, 20)
              << "\n";
    std::cout << "Sum of summ(1, 5, 10, 15, 20): " << summ(1, 5, 10, 15, 20)
              << "\n\n";

    std::cout << "Sum of sum(10, 20, 30, 40, 40, 50): "
              << sum(10, 20, 30, 40, 40, 50) << "\n";
    std::cout << "Sum of summ(10, 20, 30, 40, 40, 50): "
              << summ(10, 20, 30, 40, 40, 50) << "\n\n";

    auto x = some<int>(10);
    std::cout << x << "\n";

    using namespace literals;
    // 100_m;

    // some<tuple<int, int, int, int>, int, int, int, int>(2, 4, 6, 8);
}
