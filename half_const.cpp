// half_const
// works with:
//Compiler:
 //x86_64 gcc 12.2 
 //Compiler Arguements: 
 //-std=c++23 -Wcpp

// half_const
// std::execution::par_unseq (using std::sort)

#include <algorithm>  // std::sort
#include <exception>  // std::runtime_error
#include <execution>  // std::execution::par_unseq
#include <iostream>   // std::cout
#include <vector>     // std::vector
#include "boost/pfr.hpp"  // boost::pfr::io
#include<typeinfo> // std::typeid
#include<cmath>
#include<random>

constexpr auto fibonnacii(int y) -> int {
    bool x = (y == 0);
    return x ? y : y + fibonnacii(x - 1);

    // if()
}

template <int T>
struct fibonnaciii {
    static constexpr decltype(T) value = T + fibonnaciii<T - 1>::value;
};

template <>
struct fibonnaciii<1> {
    static constexpr decltype(1) value = 1;
};

template <int T>
struct factorial {
    static constexpr decltype(T) value = T * fibonnaciii<T - 1>::value;
};

template <>
struct factorial<1> {
    static constexpr decltype(1) value = 1;
};

template <typename T>
struct fibonnaciiii {};

template <typename T>
struct half_const {
    int count = 0;
    auto operator=(T t) {
        if (count < 1) {
            data = t;
            count++;
        } else {
            std::cout
                << "This type \"half_const\" has already been assigned to!";
            throw std::runtime_error{"Trying to assign to a const object"};
        }
    }

    friend auto operator<<(std::ostream& os, half_const& h_const) {
        std::cout << h_const.data;
    }

    T data;
};

struct basic_pod
{
    std::string s{"Hello "};
    char b{'b'};
    int asic{451};
    char x{'('};

    // basic_pod(); cant have needs to be a pod type
};

    /////////////////////////////////////////////////////
    namespace impl {
    template <class Stream, class Result, std::size_t... I>
    void fill_fileds(Stream& s, Result& res, std::index_sequence<I...>) {
        (s >> ... >> std::get<I>(res));
    }
}
    /////////////////////////////////////////////////////
    // From https://godbolt.org/z/y49lya
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2141r0.html

auto get_int()
{
    // retuns a random number
    std::random_device r;
 
    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 6);
    int mean = uniform_dist(e1);
    std::cout << "Randomly-chosen mean: " << mean << '\n';
 
    // Generate a normal distribution around that mean
    std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()}; 
    std::mt19937 e2(seed2);
    std::normal_distribution<> normal_dist(mean, 2);

    return mean;
}

struct Person
{
    Person(std::string&& name) : name_{std::move(name)} {}
    virtual const std::string name() const {return name_;}  

    private:
    std::string name_;
};

struct Buisnessman : Person
{
    Buisnessman(std::string&& name, std::string&& profession) : Person{std::move(name)}, profession_{std::move(profession)} {}
    const std::string profession() const{return profession_;}
    private:
    std::string profession_;
    // std::string name_;
};

void print_info(const Person& p) // using c++23 typeid()::operator==
{
    if(typeid(Person) == typeid(p))
    {
        std::cout << p.name() << " is not an Buisnessman\n";
    }
    else if(typeid(Buisnessman) == typeid(p))
    {
        std::cout << p.name() << " is an Buisnessman ";
        auto& emp = dynamic_cast<const Buisnessman&>(p);
        std::cout << "who works in " << emp.profession() << '\n';
    }
}

int gcd(int a, int b) {
   if (b == 0)
   return a;
   return gcd(b, a % b);
}


int main() {
    half_const<int> x;
    x = 42;
    std::cout << x;
    std::cout << "\n\n";
    try {
        x = 36;
        std::cout << x;
    } catch (std::runtime_error& x) {
        std::cout << "\n\nError: " << x.what();
    }
    std::cout << "\n";
    std::vector<int> y{1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    std::sort(std::execution::par_unseq, y.begin(), y.end());
    // parrallel vectorization.

    // std::cout << fibonnacii(24);

    std::cout << "\nfibonnaciii<24>::value: " << fibonnaciii<24>::value;
    std::cout << "\n";
    std::cout << "fibonnaciii<56>::value: " << fibonnaciii<56>::value;

    basic_pod B{};

    std::cout << "\n\n";
    std::cout << boost::pfr::io(B);

    std::cout << "\n\n";
    std::cout << boost::pfr::get<0>(B);
    std::cout << boost::pfr::get<1>(B);
    std::cout << boost::pfr::get<2>(B);
    std::cout << boost::pfr::get<3>(B);
    // std::cout << boost::pfr::get<4>(B);
    std::cout << "\n      ^^^^^\n";
    std::cout << "      BASIC\n";

    // c++ 23

    // the new warning feature of c++23
    if(false)
    // #warning "There is no other path but this one."

    // multidimensional subscript with c++23
    int arr2[10][10];
    // arr2[4, 5] = 45; // results in compiler error
    // the original syntax would have been:
    // arr2[4][5] = 45; // also results in compiler error

    // literal suffix for std::size_t.

    auto xyz = 56z;
    std::cout << "56Z || 56z typeid == " << typeid(xyz).name();

    std::cout << "\n";
    auto iint = get_int();
    if(iint != 101242453453)
    {
        // ...
    }
    else
    {
        // std::unexpected();
        // [[assume("Unlikely")]]
    }

    std::cout << "\n";
    Buisnessman p{"Bjarne Stoustup", "as a C++ Programmer and  a Computer Scienctist."};
    print_info(p);

    std::cout << "\n\n";

    std::cout << "gcd of 24, 48: " << gcd(24, 48) << "\n";
    std::cout << "gcd of 566, 789: " << gcd(566, 789) << "\n";

    // c++23 feature consteval
    if consteval
    {
        std::cout << "\nThis is happening at compile time.\n";
    }
    else
    {
        std::cout << "\nThis is not happening at compile time.\n";
    }
}
