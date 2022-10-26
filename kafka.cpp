#include <complex>
#include <cstdint>      // std::uint32_t
#include <iostream>     // std::cout
#include <type_traits>  // std::result_of

template <auto T, auto B>
struct result_of {
    static auto result = B(T);
    using value = decltype(result);
};

namespace cont {
struct binary_n {
    binary_n(unsigned long int d) { binary_data = d; }

    unsigned long int binary_data;
};

template <auto T>
struct binary_t {};
}  // namespace cont

cont::binary_n operator""_x(long double d)  // cooked form
{
    return cont::binary_n(d);
}

std::complex<long double> operator"" _i(long double d)  // cooked form
{
    return std::complex<long double>(0, d);
}

namespace kafka {

struct Kafka {
    static constexpr auto Data = 01001010010;
};

struct Kafka_consumer {};

struct Kafka_config {};

}  // namespace kafka

namespace kafka_errors {
struct Kafka_Error {};
}  // namespace kafka_errors

template <typename A, typename B>
auto result_of_t(A a, B b) {
    return decltype(b(a)){};
}

template <typename A, typename B>
auto result_of_r(A a, B b) {
    return b(a);
}

template <typename Kafka_, typename Callable>
auto get_kafka_consumer(Kafka_ k, Callable c) -> decltype(result_of_t(k, c));

auto make_lam(auto&& t) {
    auto x = [&t]() { t(); };
    return x;  // returns a callable lambda
}

template <typename A, typename B>
struct pair {
    A a;
    B b;
};

struct S {
    template <typename Kafka_, typename Callable>
    auto get_kafka_consumer(Kafka_ k, Callable c)
        -> decltype(result_of_t(k, c)) {
        if (!k) {
            return kafka_errors::Kafka_Error{};
        } else {
            return kafka::Kafka_consumer{};
        }
    }
};

template <typename Kafka_, typename Callable>
auto get_kafka_consumer(Kafka_ k, Callable c) -> decltype(result_of_t(k, c)) {
    if (!k) {
        return kafka_errors::Kafka_Error{};
    } else {
        return kafka::Kafka_consumer{};
    }
}

template <typename Kafka_, typename Callable>
auto get_kafka_consumer(kafka::Kafka (*&)())  // -> decltype(result_of_t(k, c))
{
    if (false) {
        return kafka_errors::Kafka_Error{};
    } else {
        return kafka::Kafka_consumer{};
    }
}

S s;

auto starter_function() {
    // return pair<kafka::Kafka,
    // decltype((s.get_kafka_consumer))>{kafka::Kafka{},
    // make_lam(s.get_kafka_consumer)};
    return kafka::Kafka{};
}

template <typename T>
concept is_kafka = requires(T t) { typename T::data; };

auto operator|(auto obj, auto callable)
    -> decltype(invoke_result_r(obj, callable))
// requires(is_kafka<obj>::value)
{
    return callable(obj);
}

auto and_then(auto x, auto y) { return y(x); }

int main() {
    auto x = starter_function;  //  | get_kafka_consumer;
    // get_kafka_consumer(x);
}
