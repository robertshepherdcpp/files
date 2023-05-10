#include <cstddef>
#include <iostream>
#include <utility>

namespace mlib {
template <auto N>
constexpr auto get_nth_element(auto... args) {
    return [&]<std::size_t... Indexes>(std::index_sequence<Indexes...>) {
        return [](decltype((void*)Indexes)... DontCare, auto* arg,
                  auto*... DontCareEither) { return *arg; }(&args...);
    }(std::make_index_sequence<N>{});
}

template <auto Index, auto value, auto value_two>
struct value_is_value {
    constexpr auto operator()() const {
        if constexpr (value == value_two) {
            return Index;
        } else {
            return 0;
        }
    }

    constexpr value_is_value() {}
};

template <auto value_to_find, auto... pack>
constexpr auto pack_find() {
    constexpr auto x =
        [&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return (value_is_value<indexes, pack, value_to_find>{}() + ...);
        }(std::make_index_sequence<sizeof...(pack)>{});
    if constexpr (x == 0 &&
                  mlib::get_nth_element<0>(pack...) != value_to_find) {
        return -1;
    }

    return x;
}
}  // namespace mlib

int main() {
    std::cout
        << mlib::pack_find<42, 'c', true, 3, 12, 'b', 42, false, 5, 'y'>();
    std::cout
        << mlib::pack_find<'n', 'c', true, 3, 12, 'b', 42, false, 5, 'y'>();
}
