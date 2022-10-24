#include<iostream> // std::cout
#include<vector> // std::vector
#include<string> // std::string
#include<stdexcept> // errors

namespace formt { // to format output

    auto find_braces(std::string s_p) 
    {for(int i = 0; i < s_p.size(); i++) 
        {
            if(s_p[i] == '{' and s_p[i + 1] == '}') {
                return i;
            }
        }
        return -1; }
struct format {
    explicit format(std::string);
    template<typename T>
    explicit format(std::string, T t);
    template<typename T, typename... Ts>
    explicit format(std::string, T t, Ts... ts);
};
format::format(std::string s) {
    std::cout << s << "\n";
}
template<typename T>
void func(std::string s, T t) {
    int i = find_braces(s);
    if(i == -1) {
        throw std::runtime_error("Entered variables but no /'{}/'."); }
    auto substr_v = s.substr(0, i);
    std::cout << substr_v << t;
    auto substr_v2 = s.substr(i + 2, (s.size() - i));
    std::cout << substr_v2;
}
int j = 0;
int c = 0;
template<typename T, typename... Ts>
void func(std::string s, T t, Ts... ts) {
    auto x = find_braces(s);
    j = x;
    if(j != -1) {
    auto sub_str_v = s.substr(0, j);
    std::cout << sub_str_v;
    std::cout << t;
    } else {
        throw std::runtime_error("Entered variables but no /'{}/'.");
    }
    auto w = s.substr(x + 2, s.size());
    func(w, ts...);
}
template<typename T>
format::format(std::string s, T t) {
    func(s, t);
}
template<typename T, typename... Ts>
format::format(std::string s, T t, Ts... ts) {
    func(s, t, ts...);
}
} // formt

// if [[no_return]] warning because attribute ignored
auto assert_(bool cond)
{
    if(!cond)
    {
        std::terminate();
    }
    else
    {
    }
}

template<typename A, typename B>
struct pair_ // pair_ to show that it is not a standard library type.
{
    A first;
    B second;

    pair_(A a, B b) {first = a; second = b;}
};

struct Hash
{
};

template<typename T>
struct node;

template<typename T>
struct stack;

template<typename T>
struct program_stack;

auto make_pair_(auto a, auto b) -> pair_<decltype(a), decltype(b)>;

namespace containers
{
    template<int T, int... Ts>
    struct binary
    {
        int bit;
        binary<Ts...> bits; 

        auto output_bits() // just ouputs binary
        {
            std::cout << bit;
            std::cout << "\nOutputed bit: " << bit;
            bits.output_bits();
        }
    };

    template<int T>
    struct binary<T>
    {
        int bit;

        auto output_bits()
        {
            std::cout << bit;
            std::cout << "\nOutputed bit: " << bit;
        }
    };

    auto make_binary(auto x) -> int
    {
        return static_cast<int>(x);
    }

    struct Hash
    {
        Hash(auto i)
        {
            auto x = make_binary(i);
        }
    };
}

namespace stack_manipulation
{
    void merge_two_vectors_into_v_of_pair_of_string_int(std::vector<std::string> s, std::vector<int> i_, std::vector<pair_<std::string, int>>& vpsi)
    {
        // vpsi
        for(int i = 0; i < s.size() and i < i_.size(); i++)
        {
            std::string x = s[i];
            int y = i_[i];
            pair_<std::string, int> p{x, y};
            vpsi.push_back(p);
        }
    }

    template<typename T>
    [[nodiscard]] auto get_word_count_in_nodes(node<T>& start_node, bool is_part_of_stack) -> std::vector<pair_<std::string, int>>
    {
        node<T>& current_node = start_node;

        std::vector<pair_<std::string, int>> v{}; // vector to return

        std::vector<std::string> v_s{}; // vector for storing strings or words
        std::vector<int> v_i{}; // vector for storing ints or counts of words
        assert_(is_part_of_stack); // just make sure because it is in stack_manipulation namespace.

        while(current_node.is_member_of_stack)
        {
            v_s.push_back(current_node.data_associated_with_node); // push back data with node
            auto x = std::find(v_s.begin(), v_s.end(), current_node.data_associated_with_node); // find index of where just pushbacked
            v_i[x] = v_i[x] + 1;
            current_node = current_node->next;
        }

        merge_two_vectors_into_v_of_pair_of_string_int(v_s, v_i, v);

        return v;
    }

    struct a_usless_value
    {
    };
    
    template<typename T>
    auto incryption(node<T>& v_t) -> node<T>
    {
            auto x = v_t.data_associated_with_node;
            v_t.data_associated_with_node = static_cast<int>(x);
            //v_t = v_t.next;
        
        // v_t.current_node = start_node;

        return v_t;
    }
    
    template<typename T>
    auto decryption(node<T>& v_t) -> node<T>
    {
            auto x = static_cast<T>(v_t.data_associated_with_node);
            v_t.data_associated_with_node = x;
            // v_t = v_t.current_node.next;

            return v_t;
    }

    template<typename T>
    auto go_through_stack_encrypt(program_stack<T>& stack_p)
    {
        auto x = stack_p.current_node;
        for(int i = 0; i < stack_p.size(); i++)
        {
            decryption(stack_p.current_node);
            stack_p.current_node = stack_p.current_node.next;
        }
        stack_p.current_node = x;
    }

    template<typename T>
    [[nodiscard]] auto go_through_stack_decrypt(program_stack<T>& stack_p)
    {
        auto x = stack_p.current_node;
        for(int i = 0; i < stack_p.size(); i++)
        {
            decryption(stack_p.current_node);
            stack_p.current_node = stack_p.current_node.next;
        }
        stack_p.current_node = x;
    }

    template<typename T>
    [[nodiscard]] auto go_through_stack(T& stack_p, bool b) // true if incrypt or false decrypt.
    {
        auto x = stack_p.current_node;
        for(int i = 0; i < stack_p.size(); i++)
        {
            if(!b)
            {
            auto x = decryption(stack_p.current_node);
            }
            else
            {
                auto x = incryption(stack_p.current_node);
            }
            stack_p.current_node = stack_p.current_node.next;
        }
        stack_p.current_node = x;
    }  

} // namespace stack_manipulation

auto make_pair_(auto a, auto b) -> pair_<decltype(a), decltype(b)>
{
    return pair_{a, b}; // works because of aggregate initialization.
}

template<typename T>
struct allow_assign_once
{
    int assign_once_count = 0;

    auto operator=(T t) {if(assign_once_count == 0) {data = t;}}

    T data;
};

template<typename T>
struct node
{
    T data_associated_with_node;
    bool is_member_of_stack = false; // notice defaulted to false.

    node<T>* next;
    node<T>* before;

    auto operator=(node<T> n)
    {
        data_associated_with_node = n.data_associated_with_node;
    }

    auto operator=(node<T>* n)
    {
        data_associated_with_node = n->data_associated_with_node;
    }

    auto operator==(node<T>* n)
    {
        return data_associated_with_node == n->data_associated_with_node;
    }

    auto operator==(node<T> n)
    {
        return data_associated_with_node == n.data_associated_with_node; 
    }

};

template<typename T>
struct stack
{
    node<T> node_just_before;
    allow_assign_once<node<T>> constant_node;
    node<T> current_node;
    bool is_first_initialize_nodes = true;
    node<T> last_node;
    node<T> temp_node;

    auto add_node_to_last_node(node<T> n) {last_node.next = n;}

    auto init_next_of_nodes();

    //template<T A, T... B>
    //void initialize_nodes(T A, T... B);
    using value = T;

    template<typename X, typename... Xs>
    void initialize_nodes(X A, Xs... B);

    //template<T A>
    //void initialize_nodes();
    
    template<typename X>
    void initialize_nodes(X A);

    auto find_amount_of_nodes()
    {
        int count = 0;
        temp_node = constant_node.data/*data_associated_with_node*/;
        while(temp_node != last_node)
        {
            count++;
            temp_node = temp_node.next;
        }
        return count;
    }

    auto size()
    {
        return find_amount_of_nodes();
    }
};

template<typename T>
auto stack<T>::init_next_of_nodes()
{
    for(int i = 0; i < find_amount_of_nodes(); i++)
    {
        // do something
    }
}

template<typename T>
template<typename X, typename... Xs>
void stack<T>::initialize_nodes(X x, Xs... xs)
{
    if(is_first_initialize_nodes)
    {
        constant_node.data.data_associated_with_node = x/*.data_associated_with_node*/; ///////////////////////// changed from A
    }
        current_node.data_associated_with_node = x;/////////////////////////////////////////// changed from A
        *current_node.before = node_just_before;
        node_just_before = current_node;
        current_node = current_node.next;
        std::cout << "Initialized a node with x: " << x << '\n';
        initialize_nodes(xs...);
        // std::cout << "Initialized a node with x: " << x << '\n';
        // will never reach here.
    
}

template<typename T>
template<typename X>
void stack<T>::initialize_nodes(X A)
{
    current_node.data_associated_with_node = A;
    *current_node.before = node_just_before;
    current_node = constant_node.data;
    last_node = current_node;
}

template<typename T>
struct program_stack : stack<T>
{
    auto encrypt_data() -> bool; // initialized elsewhere
                                 // bool signifies if encryption went well
};

template<typename T>
auto program_stack<T>::encrypt_data() -> bool
{
    // so have a hash map. Fill it with common keys:
    // Fill it with common keys by going throught each node incrementing a count for word
    // and which ever node is deepest use the most encryption and shallow least encryption.
    // Do this by encryption_depth_score

    return true; // just doing it for now to get rid of warning
}

// make sturctural string

constexpr auto make_node(auto i)
{
    node<decltype(i)> n;
    n.data_associated_with_node = i;

    return n;
}

template<typename T>
struct Action
{
    std::string action_s{};

    T return_act{};
    bool return_act_b{};

    Action(std::string s) {action_s = s; return_act_b = false;}
    Action(std::string s, T t)
     {
         action_s = s; 
         return_act = t; 
         return_act_b = true;
    }
};

template<typename T, typename B>
auto add_action_to_program_stack(program_stack<T>& program_s, Action<B> act)
{
    program_s.current_node = act;
    program_s.current_node = program_s.current_node.next;
}

// a structural string. Couldnt use std::string in program_stack type
struct str
{
    char* string_data;

    str(char* chars) {string_data = chars;}
};

namespace bits_and_binary
{
struct zero
{
};

struct one
{
};

template<auto T>
struct bit
{
};

template<zero T>
struct bit<T>
{
};

template<one T>
struct bit<T>
{
};
} // namespace bits_and_binary /////////////////////////////////////

auto onl()
{
    std::cout << "\n";
}

int main_2()
{
    program_stack<int> p_stack;
    auto x = p_stack.current_node;
    auto y = x.next;
    // this works but nothing is initialized

    program_stack<int> p_s;
    // p_s.initialize_nodes<5, 3, 6, 2, 7, 4, 1>();
    // dont do this becuase it needs a node of parameters not a type
    // p_s.initialize_nodes<make_node(5), make_node(3), make_node(6), make_node(2), make_node(7), make_node(4), make_node(1)>();
    
    p_s.current_node = make_node(5);

    // format teting.
    formt::format f("Hello my name is {}", 'R');
    onl();
    formt::format xyz("Good Afternoon {}", "C++");
    onl();
    formt::format abc("Good Afternoon {}", 42);
    onl();
    containers::binary<1,0,1,0,0,1> b; // for some reason gives a really wierd output.
    onl();
    b.output_bits();

    /* Examples using the incryption and decryption member function*/
    // in the stack_manipulation interface.

    stack<int> xyzY;
    //xyzY.initialize_nodes(1, 2, 3, 4); // this is what is causing the wrong output.
    stack_manipulation::go_through_stack(xyzY, true);
    onl();
    std::cout << "xyz after incryption: " << xyzY.current_node.data_associated_with_node;

    std::cout << "\nAmount of Lines in this program: " << __LINE__ + 2;
    return 0;
}
