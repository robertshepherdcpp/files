//#include <fmt/format.h>

#include <iostream>
#include <algorithm>
#include <functional>
#include <ranges>
#include <utility>

/// don't open "std", this is for demonstration purposes only

namespace formt { // to format output
    auto find_braces(std::string s_p) 
    {for(int i = 0; i < s_p.size(); i++) {
            if(s_p[i] == '{' and s_p[i + 1] == '}') {
                return i;
            } }
        return -1; }
template<typename T>
void print(std::string s, T t) {
    int i = find_braces(s);
    if(i == -1) {
        throw std::runtime_error("Entered variables but no /'{}/'."); }
    auto substr_v = s.substr(0, i);
    std::cout << substr_v << t;
    auto substr_v2 = s.substr(i + 2, (s.size() - i));
    std::cout << substr_v2; }
int j = 0; int c = 0;
template<typename T, typename... Ts>
void print(std::string s, T t, Ts... ts) {
    auto x = find_braces(s);
    j = x;
    if(j != -1) {
    auto sub_str_v = s.substr(0, j);
    std::cout << sub_str_v;
    std::cout << t;} else {
        throw std::runtime_error("Entered variables but no /'{}/'.");}
    auto w = s.substr(x + 2, s.size());
    print(w, ts...); } } // formt

namespace lib {
template <typename Func, typename... Param>
auto bind_back(Func &&func, Param &&...param) {
  return [func = std::forward<Func>(func),
          ... param = std::forward<Param>(param)]<typename... Inner>(
            Inner &&...inner) -> decltype(auto) {
    return std::invoke(func, std::forward<Inner>(inner)..., param...);
  };
}
}  // namespace std

struct Point {
  int x;
  int y;

  void displace(int x_displacement, int y_displacement) noexcept {
    x += x_displacement;
    y += y_displacement;
  }

  Point operator+(Point displacement) const {
    return Point{x + displacement.x, y + displacement.y};
  }

  void print() const { formt::print("{{},{}}\n", x, y); }
};

std::vector<Point> get_data() { return {{1, 2}, {3, 4}, {5, 6}, {42, 78}}; }

int main() {
  auto data = get_data();
  std::ranges::for_each(data, lib::bind_back(&Point::displace, 6, 5));
  std::ranges::for_each(data, &Point::print);

  for (const auto &data : get_data() | std::views::transform(lib::bind_back(
                                           std::plus<>{}, Point{7, 6}))) {
    data.print();
  }
}
