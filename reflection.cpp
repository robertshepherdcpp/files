#include<iostream>
#include<boost/pfr.hpp>
#include "boost/pfr.hpp"
#include<string>
#include<iomanip>
#include<type_traits>

struct some_person {
    std::string name;
    unsigned birth_year;
};

struct xyz
{
    int x{42};
    bool boolean{true};
};

auto print(auto& x)
requires(std::is_class<decltype(x)>::value && std::is_pod<decltype(x)>::value)
{
    boost::pfr::io(x);
}

auto print_non_class_pod(auto& x)
{
    std::cout << x << "\n";
}

struct m // pod_type for print
{
    std::string x;
    bool value;
    int y;
};

int main() {
    std::cout << std::boolalpha; // outputs true and false types
    some_person val{"Edgar Allan Poe", 1809};
    xyz X{};

    std::cout << boost::pfr::get<0>(val)                // No macro!
        << " was born in " << boost::pfr::get<1>(val);  // Works with any aggregate initializables!

    std::cout << boost::pfr::io(val);                   // Outputs: {"Edgar Allan Poe", 1809}
    std::cout << "\n";
    std::cout << boost::pfr::io(X);
    std::cout << "\n";
    m M{"Hello", true, 42};
    print(M);
}
