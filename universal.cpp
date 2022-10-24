// ideas from the unviersal template parameters paper

#include<iostream> // std::cout

template<template<typename T> typename Args>
struct xyz
{
    using value = Args<int>;
};

template<typename T>
struct x
{
    using value = T;
};

template<auto N, auto B>
struct universal
{
    static constexpr decltype(N) a = N;
    static constexpr decltype(B) b = B;
};

namespace traits
{
    template<typename T, typename B>
    constexpr bool is_same = false;

    template<typename T>
    constexpr bool is_same<T, T> = true;
}

struct A
{
    int data_member{};
};

struct B
{
    double data_member{};
};

//int main()
//{
    A a{};
    B b{};

    std::cout << traits::is_same<A, B>;
    x<int> X{};
    // xyz<x>;
//}
    //template<template <template auto...> typename F, template auto... Args>
    struct s{
};
