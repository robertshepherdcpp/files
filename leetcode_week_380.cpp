#include<vector>
#include<algorithm>
#include<utility>
#include<cassert>
#include<numeric>
#include<iostream>

namespace my
{
    template<typename A, typename B>
    struct Map
    {
        constexpr auto has(A x)
        {
            if(std::find(keys.begin(), keys.end(), x) != std::end(keys))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        constexpr auto operator[](A x)
        {
            for(int i = 0; i < keys.size(); i++)
            {
                if(keys[i] == x)
                {
                    return values[i];
                }
            }
            if(!has(x))
            {
                return A{};
            }
        }

        auto at(int i)
        {
            return values[i];
        }

        auto append(std::pair<A, B> p)
        {
            keys.push_back(p.first);
            values.push_back(p.second);
        }

        auto value_assign(A key, B x)
        {
            for(int i = 0; i < keys.size(); i++)
            {
                if(keys[i] == key)
                {
                    values[i] = x;
                }
            }
        }

        auto accumulate_values()
        {
            return std::accumulate(values.begin(), values.end(), 0);
        }

        Map() {}

        std::vector<A> keys{};
        std::vector<B> values{};
    };
};

auto test(std::vector<int> v) -> int // occurences
{
    my::Map<int, int> m{};
    int i = 0;
    for(const auto x : v)
    {
        if(m.has(x))
        {
            m.value_assign(x, m.at(i) + 1);
        }
        else
        {
            m.append(std::pair<int, int>{x, 1});
        }
        i++;
    }
    return m.accumulate_values();
}

int main()
{
    std::cout << (test(std::vector<int>{1,2,3,4,5})); // should print 5
}
