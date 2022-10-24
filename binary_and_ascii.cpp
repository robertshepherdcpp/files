#include<iostream> // std::cout
#include<vector> // std::vector

template<int T, int... Ts>
struct binary;

template<typename T, typename... Ts>
struct binary2;

template<typename T, typename... Ts>
auto make_binary(T t, Ts... ts)
{
    binary2/*<t, ts...>8*/ b(t, ts...);
    return b;
}
template<int T, int... Ts>
struct binary
{
    int bit = T;
    // binary<decltype(Ts)...> bits = binary<Ts...>;
    auto output_binary()
    {
        std::cout << bit;
        bit;//its.ouptut_binary();
    }
};

template<typename T, typename... Ts>
    struct binary2
    {
        int bit;
        binary2<Ts...> bits; 

        auto output_bits() // just ouputs binary
        {
            std::cout << bit;
            std::cout << "\nOutputed bit: " << bit;
            bits.output_bits();
        }

        binary2(T t, Ts... ts)
        {
            bit = t;
            bits = make_binary(ts...);
        }

        binary2() {} // does nothing because it doesnt need to/
    };

template<typename T>
struct binary2<T>
{
    int bit;

    auto output_bits()
    {
        std::cout << bit;
    }

    binary2(T t) {bit = t;}
    binary2() {}; // does nothing because it doesnt need to.
};

auto onl()
{
    std::cout << '\n';
}

template<typename T>
auto for_loop_algo(int start, int end, T t)
{
    for(start; start < end; start++)
    {
        t();
    }
}

auto out_ascii(auto x)
{
    std::cout << static_cast<int>(x);
}
    int main()
    {
        binary2 b(1,0,1,1);
        b.output_bits();
        onl();
        std::vector<char> alphabet{'a','b','c','d','e','f','g','h','i','j','k','l',
                                   'm','o','p','q','r','s','t','u','v','w','x','y','z'};
        std::cout << "The chars in ascii or binary: \n";
        for(int i = 0; i < 25; i++) // 25 because otherwise it outputs another character not needed, out of range access.
        {
            std::cout << alphabet[i] << ": ";
            std::cout << static_cast<int>(alphabet[i]);
            onl();
        }
        onl();
        std::cout << "ascii of @: ";
        out_ascii('@');
        onl();
        std::cout << "static_cast<char>(64): ";
        std::cout << static_cast<char>(64);
    }
