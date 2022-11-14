#include<iostream> // std::cout
#include<cstddef> // std::size_t

struct VoidType
{
    // no implemenatation, doesnt need one
};

template<typename T>
struct initializer_list
{
    // a bit like a tuple but in a list form interface instead

    initializer_list(); // default constructor
    
    template<typename A>
    initializer_list(A a);

    template<typename A, typename... B>
    initializer_list(A a, B... b);

    std::size_t size_list;
    T _list[1];
};

template<typename T>
initializer_list<T>::initializer_list()
{

}

template<typename T>
template<typename A>
initializer_list<T>::initializer_list(A a)
{
    size_list = 1;
    _list[0] = a;
}

template<typename T>
constexpr auto ParameterPackSize(T t)
{
    return 1;
}

template<typename T, typename... Ts>
constexpr auto ParameterPackSize(T t, Ts... ts)
{
    return 1 + ParameterPackSize(ts...);
}

template<typename T, auto Size, typename A, typename... B>
auto assign_list(T (&arr)[Size], int index, A a, B... b)
{
    arr[index] = a;
    assign_list<T, Size, B...>(arr, index + 1, b...);
}

template<typename T, auto Size, typename A>
auto assign_list(T (&arr)[Size], int index, A a)
{
    arr[index] = a;
}

template<typename T>
template<typename A, typename... B>
initializer_list<T>::initializer_list(A a, B... b)
{
    size_list = 1 + ParameterPackSize(b...);
    delete[] _list;
    _list = new T[size_list];
    assign_list(_list, 0, a, b...);
}

template<typename T = int>
struct range
{
    auto reverse(); // reverse the current range
    auto print(); // print the range like: [...]
    auto get(); // return the current range
    auto zero(); // zero all elements in the range
    auto part(std::size_t start, std::size_t end) -> decltype(auto); // get a ceratain part of the range
    
    template<auto Size>
    range(T(&arr)[Size]); // constructor taking an array

    // doesnt need a template parameter as is of size one already
    // template<typename Size = VoidType>

    range(T(&arr)[1]); // constructor taking array of size 1

    range(range<T>& r); // copy constructor

    range(range<T>&& r); // move constructor

    range(initializer_list<T>& list); // constructor taking an initializer list.

    std::size_t size_range = 1; // will always be greater than one
    T _range[1];
};

template<typename T>
range<T>::range(T(&arr)[1])
{
    _range[0] = arr[0]; // range is already 1. So now point resising the array.
}

// TODO: modify size_range when modifying _range

template<typename T>
range<T>::range(range<T>& r)
{
    if(size_range != r.size_range)
    {
        delete[] _range;
        _range = new T[r.size_range];
    }

    size_range = r.size_range;
    for(int i = 0; i < r.size_range; i++)
    {
        _range[i] = r._range[i];
    }
}

template<typename T>
range<T>::range(range<T>&& r)
{
    if(size_range != r.size_range)
    {
        delete[] _range;
        _range = new T[r.size_range];
    }

    size_range = r.size_range;
    for(int i = 0; i < r.size_range; i++)
    {
        _range[i] = std::move(r._range[i]);
    }
    for(int i = 0; i < r.size_range; i++)
    {
        _range[i] = T();
    }
}

template<typename T>
template<auto Size>
range<T>::range(T(&arr)[Size])
{
    delete[] _range;
    _range = new T[Size];
    for(auto i = 0; i < Size; i++)
    {
        _range[i] = arr[i];
    }

}

auto increment_decrement(auto& one, auto& two)
{
    one++; // because is refernce modifies original value.
    two--; // decrements original value.
}

template<typename T>
auto range<T>::reverse()
{
    // implementation of reverse
    auto x = size_range;
    for(auto i = 0; i < size_range; increment_decrement(i, x))
    {
        auto temp = _range[x];
        _range[x] = _range[i];
        _range[i] = _range[x];
    }

    x = 0;
}

template<typename T>
auto range<T>::print()
{
    std::cout << "\n[";
    for(int i = 0; i < size_range; i++)
    {
        std::cout << _range[i];
        if(i != size_range - 1)
        {
        std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

template<typename T>
auto range<T>::get()
{
    return _range;
}

template<typename T>
auto range<T>::zero()
{
    for(auto i = 0; i < size_range; i++)
    {
        _range[i] = T();
    }
}

auto increment_increment(auto& a, auto& b)
{
    a++;
    b++;
}

template<typename T>
auto range<T>::part(std::size_t start, std::size_t end) -> decltype(auto)
{
    T arr[end - start];
    int count = 0;
    for(std::size_t i = start; i < end; increment_increment(count, i))
    {
        arr[count] = _range[i];
    }
    return arr;
}

int main()
{
    //range r{initializer_list(1, 2, 3, 4)};

    int arr[4]{1, 2, 3, 4};

    range r{arr};
}
