#include<vector> // std::vector
#include<source_location> // std::source_location

struct Network;

struct IP
{
    std::string_view ip{"000.000.000"};
    Network network{};
};

struct message
{
    auto log(std::string_view v)
    {
        str_v = v;
    } 

    std::string_view str_v{};

    auto export(IP ip_export)
    {
        Ip.network.add(*this);
    }
};

namespace networks
{
void log(const std::string_view& message, const std::source_location& location =
                                              std::source_location::current()) 
{
    std::cout << "|     File|line|        |Function Name|Message|\n";
    std::cout << "info:" << location.file_name() << ":" << location.line()
              << " " << location.function_name() << " " << message << '\n';
}
    struct socket
    {
        auto upload_data(auto&& a);
        auto import_data();
    };

    auto make_socket()
    {
        return socket();
    }
}

template<typename T>
struct Data
{
    T data;
}

struct Network
{
    std::vector<networks::socket> v{};

    template<typename T>
    auto export(Data<T> d);

    template<typename T>
    auto import(Data<T> d);

    auto add(auto&& x);
    auto take(auto&& x);

    Network(networks::socket s)
    {
        v.push_back(s);
    }

    Network()
    {
        // Do Nothing...
        // Vector is already initialized.
    }
};

template<typename T>
auto Network::export(Data<T> d)
{
    v[0].upload_data(d);
    auto x = v.pop_front();
    return x;
}

template<typename T>
auto Network::import(Data<T> d)
{
    v[0].import_data();
    auto x = v.pop_front();
    return x;
}

int main_2()
{
    Network();

    networks::log("Hello C++");
}

int main()
{
    main_2();
}

