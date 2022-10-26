#include<string>
#include<iostream>
#include<cstdlib>
#include<map>
#include<utility>
#include<vector>

int global_long_int = 0;
int global_index = 0;
bool global_bool = false;
int __i_ = 0;
std::vector<int> i{};
bool b = false;
bool get_has_been_called = false;

constexpr auto return_char_int(char& i)
{
    switch(i)
    {
        case '1':
        return 1;   break;
        case '2':
        return 2;   break;
        case '3':
        return 3;   break;
        case '4':
        return 4;   break;
        case '5':
        return 5;   break;
        case '6':
        return 6;   break;
        case '7':
        return 7;   break;
        case '8':
        return 8;   break;
        case '9':
        return 9;   break;
        default:
        return -1; break;
    }
}

auto get(auto t)
{
    global_index = 0;
    global_long_int = 0;
    global_bool = true;
    b = false;
    return t; // doesnt catch exeptions.
}

auto get(auto t, auto... ts)
{
    if(!b)
    {
    i.push_back(global_index);
    }
    b = true;
    if(global_index == global_long_int)
    {
        global_long_int = 0;
        global_index = 0;
        global_bool = true;
        b = false;
        return t;
    }
    global_long_int++;
    if(get(ts...))
    {
        return get(ts...);
    }
    else
    {
        return t;
    }
}

namespace formttwo { // to format output
    struct Num
    {
    };

    template<typename T, typename... Ts>
    auto find_braces(std::string s_p, T t, Ts... ts) 
    {
        for(int i = 0; i < s_p.size(); i++) 
        {
            if(s_p[i] == '{' and s_p[i + 1] == '}') {
                return std::pair<decltype(t), int>(t, i);
            }
            else if(s_p[i] == '{' and s_p[i + 2] == '}')
            {
                auto xyz__ = s_p[i + 1];
                int zyz_ = return_char_int(xyz__);
                global_index = zyz_;
                return std::pair/*<decltype(get<zyz_>(t, ts...)), int>*/(get(t, ts...), i);
            }
        }
        return std::pair(t, -1);
     }

    template<typename T>
    auto find_braces(std::string s_p, T t) 
    {
        for(int i = 0; i < s_p.size(); i++) 
        {
            if(s_p[i] == '{' and s_p[i + 1] == '}') {
                return std::pair<decltype(t), int>(t, i);
            }
            else if(s_p[i] == '{' and s_p[i + 2] == '}')
            {
                auto xyz__ = s_p[i + 1];
                int zyz_ = return_char_int(xyz__);
                return std::pair/*<decltype(get<zyz_>(t, ts...)), int>*/(t, i);
            }
        }
        return std::pair(t, -1);
     }

template<typename T>
void func(std::string s, T t) {
    auto i = find_braces(s, t);
    // if(i == -1) 
    // {
    //     throw std::runtime_error("Entered variables but no /'{}/'."); 
    // }
    auto substr_v = s.substr(0, i.second);
    std::cout << substr_v << i.first;
    std::string substr_v2 = "";
    if(get_has_been_called)
    {
    substr_v2 = s.substr(i.second + 4, (s.size() - i.second));
    }
    else
    {
        substr_v2 = s.substr(i.second + 3, (s.size() - i.second)); // could be i.second + 2
    }
    std::cout << substr_v2;
    std::cout << "\n";
    get_has_been_called = false;
}
int j = 0;
int c = 0;
template<typename T, typename... Ts>
void func(std::string s, T t, Ts... ts) 
{
    if(b)
    {
        //if(__i_ == 0)
    }
    auto x = find_braces(s, t, ts...);
    j = x.second;
    if(j != -1) {
    auto sub_str_v = s.substr(0, j);
    std::cout << sub_str_v;
    std::cout << x.first;
    } else {
        throw std::runtime_error("Entered variables but no /'{}/'.");
    }
    std::string w = "";
    if(get_has_been_called)
    {
    w = s.substr(x.second + 4, s.size());
    }
    else
    {
        w = s.substr(x.second + 3, s.size());
    }
    func(w, ts...);
}
} // formt

struct Self
{
};

auto func(Self& self)
{

}

int function()
{
    formttwo::func("{}\n", 4242);
    formttwo::func("Hello There {1} my freinds called {0}", "Sue", "Phil");
}
