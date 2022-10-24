#include <any>        // std::any
#include <atomic>     // std::atomic
#include <chrono>     // std::chrono::system_clock
#include <cstddef>    // std::size_t
#include <future>     // std::packaged_task, std::future
#include <iostream>   // std::cout, std::wcout
#include <optional>   // std::optional
#include <semaphore>  // std::semaphore
#include <string>     // std::string
#include <thread>     // std::jthread
#include <utility>    // std::integer_sequence
#include <variant>    // std::variant
#include <vector>     // std::vector

// https://godbolt.org/z/zzzb5Yj3q string implementation is here.

int calculate_sum(int i, int b) {
    std::cout << i + b << "\n";

    return i + b;
}

auto fibonacii(int a, int b, int c) {
    std::vector<int> fibs{};
    auto first = a;
    auto second = b;
    int i = 0;
    fibs.push_back(a);
    fibs.push_back(b);
    while (i < c) {
        std::cout << a << ", " << b << ", ";
        std::cout << a + b;
        first = b;
        second = a + b;
        // fibs.push_back(a); implemented above, other wise would be pushing
        // back the same things fibs.push_back(b); multiple times
        fibs.push_back(a + b);
    }
    return fibs;
}

template <typename T, T... ints>  // a way to find length of parameter pack with
                                  // std::integer_sequence.
void print_sequence(std::integer_sequence<T, ints...> int_seq) {
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}

int main_2() //
{
    // compiler explorer doesnt seem to work with threads.

    std::packaged_task<int(int, int)> task{calculate_sum};
    auto future{task.get_future()};
    std::jthread{move(task), 24, 42};

    // std::async

    auto future_2 = std::async(calculate_sum, 42, 24); // need to assign to
    // future otherwise keeps on waiting 
    auto x = future_2.get();

    // parrallel async or concurrent async for fibonnacii.
    // auto theFuture = std::async(std::move(fibonacii), 0, 1); // results in
    // an error.

    // Semaphores
    std::counting_semaphore semaphore{4}; // 4 threads
    std::vector<std::jthread> jthreads{};
    for(int i{0}; i < 10; i++)
    {
        jthreads.push_back(std::jthread{
            [&semaphore]{
                semaphore.acquire();

                semaphore.release();
            }
        });
    }

    //std::wcout << "Hello";

    return 0;
}

namespace lib {
struct true_type {};
struct false_type {};

template <typename A, typename B>
struct is_same : true_type {
    static constexpr bool value = true;
};

template <typename A>
struct is_same<A, A> : false_type {
    static constexpr bool value = false;
};
}  // namespace lib

auto func(bool b) {
    return b ? std::optional<std::string>{"Hello"} : std::nullopt;
}

using namespace std::chrono_literals;

auto assert_(bool b, std::string expression = " ") {
    if (b) {
        std::cout << "The expression " << expression << "passed";
    } else {
        std::cout << "The expression " << expression
                  << "failed. Calling std::terminate.";
        auto x = std::chrono::system_clock::now();
        // while(std::chrono::duration_cast(std::chrono::system_clock::now() -
        // x) != 5s)
        std::this_thread::sleep_for(5s);
        std::terminate();
    }
}

template <typename T>
struct A {
    using type = T::type;
};

template <typename T>
void g(T, typename A<T>::type);

int main() {
    std::wcout << "Hello";
    std::cout << "\n";
    // std::wcout << L"罗伯特";

    std::atomic<int> atom{};
    // atom.wait();
    atom.notify_all();

    auto xyz = func(true);
    auto y = func(false);
    static_assert(!lib::is_same<decltype(xyz), decltype(y)>::value);

    // these two types are not of the same type even though they came from the
    // same function call. but with different arguements.

    assert_(5 != 6.5, "5 != 6.5");

    // print_sequence(2, 3,4 ,5 ,6, 4, 3, 5, 2, 4, 3, 54); // doesnt work needs
    // integer_seq as arg.
    print_sequence(std::integer_sequence<int, 9, 2, 5, 1, 9, 1, 6>{});

    std::cout << "With std::variant you can have lots different types and "
                 "assign them as follows";
    std::variant<int, std::string> var{42};

    auto x = std::get<int>(var);
    assert_(x == 42);

    var = "Hello";

    auto xy = std::get<std::string>(var);
    assert_(xy == "Hello");

    // std::any

    std::any a = 14;
    std::cout << "a.type().name():\tstd::any_cast<int>(a);";
    std::cout << a.type().name() << ":\t" << std::any_cast<int>(a) << '\n';

    return 0;
}
