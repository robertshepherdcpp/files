#include <iostream>  // std::cout
#include <string>    // std::string
#include <variant>   // std::variant
#include <math.h>

#define type auto
#define not_equal_to !=
#define is_equal_to ==
#define str std::string
#define nl std::cout << "\n"
#define freind friend

template<typename T>
struct s
{
    s(T t) : t_{t} {}
    s() : t_{} {}

    friend auto operator==(s<T>& z, s<T>& y)
    {
        return z.t_ == y.t_;
    }

    freind auto operator+(int y, s<T>& z)
    {
        return y + z.t_;
    }

    friend auto operator+(s<T>& z, int y)
    {
        return z.t_ + y;
    }

    friend auto operator+(s<T>& x, s<T>& y)
    {
        return x.t_ + y.t_;
    }

    freind auto operator<<(std::ostream& o, auto x)
    {
        o << x;
    }

    T t_;
};

template<typename T>
auto make_s(T t) -> s<T>
{
    return s{t};
}

int main() {
    {
        auto x = 3 & ((16 / 4) * 8);
        std::cout << x;
        std::cout << "\n";
        auto y = 67 & 52;
        std::cout << y;
    }
    {
        std::variant<int, double, float> v{5};
        auto l = std::get<int>(v);
        std::cout << "\n" << l << "\n";
        v = M_PI;
        auto y = std::get<double>(v);
        std::cout << y << "\n";
    }
    {
        str s = "xyz";
        str x = "yzx";

        /*if (s is_equal_to x) { always true.
            std::cout << "x: " << x << " Is equal to s: " << s << ".";
        } else *///if (s != x) 
        {
            std::cout << "x: " << x << " Is not equal to s: " << s << ".";
        }
    }
    {
        nl;
        s S{5};
        s Y{10};
        auto y = S + Y;
        std::cout << y << "\n";

        auto x = S + 10;

        std::cout << S + 10 + Y;
        // std::cout << make_s(true) + 5;
    }
}
