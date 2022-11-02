#include<iostream> // std::cout
#include<chrono> // std::chrono
#include<string> // std::string, std::string_view
#include<vector> // std::vector
#include<utility> // std::pair
#include<any> // std::any
#include<optional> // std::optional
#include<typeinfo> // typeid

// just seeing how long std::puts and std::cout take.
// just carrying on from timur doumlers talk.

// using std::literals::chrono_literals;

/*
* 
 __      ___                 _    _____ _             _ _        
 \ \    / (_)               | |  / ____| |           | (_)       
  \ \  / / _ ___ _   _  __ _| | | (___ | |_ _   _  __| |_  ___   
   \ \/ / | / __| | | |/ _` | |  \___ \| __| | | |/ _` | |/ _ \  
    \  /  | \__ \ |_| | (_| | |  ____) | |_| |_| | (_| | | (_) | 
     \/   |_|___/\__,_|\__,_|_| |_____/ \__|\__,_|\__,_|_|\___/  
                                                                 
                                                                 
// https://patorjk.com/software/taag/#p=display&f=Big&t=Visual%20Studio%20
*/

using namespace std::string_literals;

namespace universal
{
	struct True {};
	struct False {};

	True true_t{};
	False false_t{};
}

namespace errors
{
	struct const_error { std::string error_str; };
	struct generic_error { std::string error_str; };
	struct string_parse { std::string error_str; };
}

struct struct_string
{
	auto operator=(const char*);

	const char* s;
};

auto struct_string::operator=(const char* chars)
{
	s = chars;
}

struct simple_pod
{
	std::string str{};
};

namespace math
{
	int gcd(int a, int b) {
		if (b == 0)
			return a;
		std::cout << "b: " << b << " a: " << a << "\n";
		return gcd(b, a % b);
	}

}

template<typename T>
struct half_const
{
	int count = 0;

	half_const<T> operator=(T& x)
	{
		if (count < 1)
		{
			std::cout << "You have now used your assignment of half_const.";
			data = x;
			count++;
			return *this;
		}
		else
		{
			std::cout << "This type is now const you cannot assign to it!\n Throwing now:";
			// thow errors::const_error{};
			return *this;
		}
	}

	half_const()
	{
		data = {};
	}

	half_const(T t)
	{
		data = t;
	}

	auto get_val()
	{
		return data;
	}

private:

	T data;
};

// using std::literals;

struct Leaf {};
struct Node;

template<typename... Ts> 
struct overload : Ts...
{
	// using Ts::()...;
};

// a kind of idea from ben deanes talk/ timur doumlers's talk at cppcon 2022


template<typename X, typename Y>
struct overload2
{
	X x;
	Y y;
};

struct Node
{
	Leaf left, right;
};

auto find_leaf()
{
	//auto x = overload2{
	//	[&](Leaf& l) {return 1; }
	//	[](Node* n) {return {n->left, n->right}; }
	//}
}

auto assert(bool expression)
{
	if (!expression)
	{
		std::cout << "Assert Failed Calling \'std::abort()\' now.\n";
		std::abort();
	}
	else
	{

	}
}

template<int index, typename type>
auto get_first_n_of(auto& x)
{
	std::vector<type> v{};
	for (int i = 0; i < x.size(); i++)
	{
			if (i != index)
			{
				v.push_back(x[i]);
			}
	}
	type s{};
	int index_two = 0;
	for (auto i : v)
	{
		s[index_two] = i;
		index_two++;
	}
	return s;
}

template<typename T>
auto make_vector(T t)
{
	std::vector<T> vec = { t };
	return vec;
}

template<typename T, typename... Ts>
auto make_vector(T t, Ts... ts)
{
	std::vector<T> vec = { t, ts... };
	return vec;
}

auto is_equal(auto& x, auto& y)
{
	if (x.size() != y.size())
	{
		return false;
	}
	for (int i = 0; i < x.size(); i++)
	{
		if (x[i] != y[i])
		{
			return false;
		}
	}
	return true;
}

auto parser(std::string& str)
{
	if (str[0] == '/' && str[1] == '/' && str[2] == '/' && str[3] == '/')
	{
		std::cout << "It is looking promising!";
	}
}

namespace traits
{
	struct true_type 
	{
		/*Just an identifier*/
		constexpr static bool value = true;
	};
	struct false_type 
	{
		/*Just an identifier*/ 
		constexpr static bool value = false;
	};

	template<typename T>
	struct make_pointer
	{
		using value = T*;
	};
}

namespace type_properties
{
	template<typename T>
	struct property
	{
		using value_type = T;
		using ref = T&;
		using pointer = T*;
		using refref = T&&;
		using pointerpointer = T**;
		T default_construct = T{};
	};
}

template<typename T, typename B>
struct is_an : traits::false_type
{
};

template<typename T>
struct is_an<T, T> : traits::true_type
{
};

struct a
{
	int b;
	bool a;
};

struct b
{
	std::string s = "HEllo";
	char c = 'C';
};

// forward declaration
template<typename T>
struct unique_pointer;

namespace make
{
	template<typename T, typename... Args>
	auto make_unique(T t, Args... args)
	{
		return unique_pointer<T>(new T(std::forward<Args>(Args...) ...));
	}
}

// because cant access internet for which header has std::unique_pointer: implemented myself

template<typename T>
struct unique_pointer // turns it was in the memory header file: #include<memory>
{
	unique_pointer(T t)
	{
		using val = typename traits::make_pointer<T>::value;
		val value = {};
		value = t;
		data = value;
	}

	unique_pointer(T* t)
	{
		std::cout << "unique_pointer(T* t) / constructor taking a pointer arg,  has been called.\n";
		if (data)
		{
			data = t;
		}
		else
		{
			data = new T();
			data = t;
		}
	}

	unique_pointer()
	{
		std::cout << "unique_pointer() / default constructor has been called.\n";
		data = new T();
	}

	~unique_pointer()
	{
		std::cout << "~unique_pointer() / destructor has been called.\n";
		delete data;
	}

	auto get_data() const
	{
		std::cout << "get_data() called.\n";
		return *data;
	}

	// decltype(auto) to preserve * and &'s.
	decltype(auto) get_data_pointer() const
	{
		return data;
	}

	T* data;
};

struct Leaf2
{
	// doesnt need an implementation. if it is a leaf, it 
	// is a leaf, no extra checking needed
};

struct Node2
{
	Node2* left;
	Node2* right;
	Node2* next;

	int Data{};
};

struct Tree2
{
	Node2 Left, Right;
	Node2 Curr;
};

auto find_nodes_n() -> bool;

template<typename T>
auto find_nodes(Tree2& t, T& LamToCall) -> bool// using CTAD
{
	std::cout << t.Curr.Data << "\n";
	std::cout << "Finding Left Nodes.";
	// find_nodes_n(t.Left);
	std::cout << "Finding Right Nodes.";
	// find_nodes_n(t.Right);

	return true;
}

//auto find_nodes_n(Node2* node) -> bool
//{
//	if (node.left != nullptr)
//	{
//		std::cout << node.Data;
//		find_nodes_n(node.left);
//	}
//
//	return true;
//}

namespace std_cast // so the call to move is ambiguous.
{
	template<typename Arg>
	auto move(Arg arg) // what move really is.
	{
		return static_cast<std::remove_reference<decltype(arg)>::type&&>(arg);
	}
}

template<template<typename T> typename T_T>
struct underlying_type
{
	// T value_type(T{});
	// using value = T;
};

template<typename T>
struct s
{
	T t{};
};

template<typename T>
struct another_type
{
	T t = T{};
};

template<int i> struct D { D(void*); operator int(); };
template<int p, int i> struct is_prime
{
	enum{prim = (p % i) && is_prime<(i > 2 ? p : 0), i - 1>::prim };
};
template<int i> struct Prime_int
{
	Prime_int<i - 1> a;
	enum { prim = is_prime<i, i - 1>::prim };
	void f() { D<i> d = prim; }
};

template<>
struct is_prime<0, 0> { enum { prim = 1 }; };
template<>
struct is_prime<0, 1> { enum { prim = 1 }; };
template<>
struct Prime_int<2> {
	enum { prim = 1 }; void f()
	{
		// D<2> d = int(prim);
	}
#ifndef LAST
#define LAST 10
#endif
	int main()
	{
		Prime_int<LAST> a;
	}
};

namespace errors
{
	enum class error_types
	{
		Runtime_error = 1, Const_error, Parse_error, DataType_error, No_Error
	};

	auto output_appropriate_error(int i)
	{
		switch (i)
		{
		case 1:
			std::cout << "Runtime_error.\n";         break;
		case 2:
			std::cout << "Const_error.\n";           break;
		case 3:
			std::cout << "Parse_error.\n";           break;
		case 4:
			std::cout << "DataType_error.\n";        break;
		case 5:
			std::cout << "No_Error.\n";              break;
		default:
			std::cout << "Invalid value entered.\n"; break;
		}
	}
};

template<typename T>
struct ErrorOr
{
	ErrorOr()
	{
		variable;
		current_type = false;
	}

	ErrorOr(T t)
	{
		variable = t;
		current_type = false;
	}

	ErrorOr(decltype(errors::error_types::No_Error)& s)
	{
		Error = s;
		current_type = true;
	}

	auto operator=(T t)
	{
		variable = t;
		current_type = false;
	}

	auto operator=(decltype(errors::error_types::No_Error)& s)
	{
		Error = s;
		current_type = true;
	}

	auto get_val(traits::true_type& s)
	{
		return Error;
	}

	auto get_val(traits::false_type& s)
	{
		return variable;
	}

	auto is_error()
	{
		return current_type;
	}

	bool get()
	{
     if (!current_type) // variable is active
    {
	      return true;
    }
else
{
	return false;
}
	}

	// false = variable, and true = Error
	bool current_type = false;

	decltype(errors::error_types::No_Error) Error = errors::error_types::No_Error;
	T variable = T{};

};

template<typename T>
struct add_const
{
	using value_type = const T;
};

template<typename T>
struct add_const<T const>
{
	using value_type = const T;
};

template<typename T>
struct is_const : traits::false_type
{
};

template<typename T>
struct is_const<T const> : traits::true_type
{
};

template<typename T>
ErrorOr<double> function()
{
	return {};
}

template<auto Callable, auto Arg, auto... Args>
struct invoke_t
{
	static const auto value = Callable(Arg, Args...);
	using type = decltype(value);
};

template<auto Callable, auto Arg>
struct invoke_t<Callable, Arg>
{
	static const auto value = Callable(Arg);
	using type = decltype(Callable(Arg));
};

constexpr auto func(bool b)
{
	return b ? !b : b;
}


namespace OneTrueLib
{
	template<auto T>
	auto get()
		requires(T.Bool == true)
	{
		return T.first;
	}

	template<auto T>
	auto get()
		requires(T.Bool == false)
	{
		return T.second;
	}

	template<auto T>
	auto get()
	{
		return T.first;
	}
}
template<typename A, typename B>
struct OneTrue
{
	A first;
	B second;
	bool Bool{};

	OneTrue() : first{}, second{}
	{
		// by default use the first as the value.
		Bool = true;
	}

	OneTrue(A t) : first{ t }, second{}, Bool{true}
	{
		// first is the type
	}

	OneTrue(B t) : first{}, second{ t }, Bool{false}
	{
		// second is the type
	}

	OneTrue(bool b) : Bool{ b } {}

};

// return type is a unvirsal::false_t or a unviral::true_t, but see below.
// this function requires you to do: universal::get<__Return_Type__>(); which will give you the return type of the function.
auto VERIFY(bool expression, std::string& expression_str) -> OneTrue<decltype(universal::false_t), decltype(universal::true_t)>
{
	std::cout << "Verifying the the expression " << expression_str << " is: " << expression;
	if (!expression)
	{
		std::cout << "\nExpression Failed.\n";
		return universal::false_t; // default constructs a OneTrue type because of trailing return type.
	}
	else
	{
		std::cout << "\nExpression Passed.\n";
		return universal::true_t; // default constructs a OneTrue type because of trailing return type.
	}
}

template<typename T>
struct DataMember
{
	auto operator=(T t)
	{
		__Data = t;
	}

	DataMember(T t)
	{
		__Data = t;
	}

	auto clear()
	{
		__Data = ~T();
	}

	T __Data{};
};

struct my_container
{
	my_container() {}
	my_container(int i) { d_m_i = i; }

	auto and_then(auto LambdaExpression)
	{
		LambdaExpression(d_m_i);
		return *this;
	}

	DataMember<int> d_m_i = 42;
};

std::string empty_str = "";

auto MUST(bool expression, std::string& expression_str = empty_str) -> void
{
	if (!expression)
	{
		std::cout << expression_str << " failed calling std::abort now.\n";
		std::abort();
	}
	else
	{
		std::cout << empty_str << " passed.\n";
	}
}

// returns true if all are true and false if one is not true.
template<typename... Args>
bool all(Args... args)
{
	return (... and args);
}

template<auto t, auto... ts>
struct all_
{
	static constexpr bool value = bool(t);
	static constexpr bool values = all_<ts...>::value;

	auto is() -> bool
	{
		return value && values;
	}
};

template<auto t>
struct all_<t>
{
	static constexpr bool value = t;
};

int main()
{
	auto start_puts = std::chrono::system_clock::now();
	std::puts("HEllo");
	auto end_puts = std::chrono::system_clock::now() - start_puts;
	std::cout << "\n";
	std::cout << "std::puts(\"HEllo\") took:   " << end_puts.count() << "\n";

	std::cout << "\n";
	auto start_cout = std::chrono::system_clock::now();
	std::cout << "HEllo";
	auto end_cout = std::chrono::system_clock::now() - start_cout;
	std::cout << "\n\n";
	std::cout << "std::cout << \"Hello\" took: " << end_cout.count() << "\n";

	//struct_string struct_string_ = "Goodbye";
	// h_const = struct_string_;
	// struct_string another_string = "HEllo";

	std::cout << "\n";
	half_const<simple_pod> syz_c{};
	syz_c = simple_pod{ "Hello" };
	syz_c = simple_pod{ "Goodbye" };
	syz_c = simple_pod{ "Good Morning" };
	simple_pod syz{};
	syz.str = "Hello";

	auto xy_ = math::gcd(60, 96);
	std::cout << xy_;
	std::cout << "\n\n";
	auto gcd_result = math::gcd(512, 132);
	std::cout << gcd_result << "\n";

	std::cout << "---------------------------------------------------\n";
	std::cout << "Traits and others\n";
	std::cout << "---------------------------------------------------\n\n";

	a A{};
	b B{};

	bool is_an_a_b = is_an<decltype(A), decltype(B)>::value;
	std::cout << std::boolalpha << "is_an<a, b>::value: " << is_an_a_b << "\n";

	a Atwo{};

	bool is_an_a_a = is_an<decltype(A), decltype(Atwo)>::value;
	std::cout << std::boolalpha << "is_an<a, a>::value: " << is_an_a_a << "\n";
	std::cout << "\n";

	std::cout << "---------------------------------------------------\n";
	std::cout << "User Defined make_unique\n";
	std::cout << "---------------------------------------------------\n\n";

	// inspiration from Ranier Grimm's c++'s Core Guidlines Explained.
	// a make_unique using variadic templates

	auto x = make::make_unique(42);

	//another_type<bool> b{};
	//s < decltype(b) > Y{};

	//underlying_type<Y>::value x = 42;

	// a blatent error:

	auto v = 5 * '£';
	std::cout << "5 * \'£\' / Pound Sign : is " << v << " or " << 5 * '£' << "\n";
	// std::optional<decltype(errors::error_types::No_Error), double> v{};
	auto error_or_double = ErrorOr<double>{};
	auto error_or = function<int>();
	auto error_or_two = error_or_double;
	bool boolean_val = error_or.get();
	if (boolean_val)
	{
		//error_or.get_val(traits::true_type{});
		std::cout << "The error_or value is: " << int(error_or.Error) << " which is the error type.\n";
		std::cout << "The error type was a ";
		errors::output_appropriate_error(int(error_or.Error));
		if (int(error_or.Error) == 5)
		{
		std::cout << "The error_or value is: " << error_or.variable << " which is the variable type\n";
        }
	}
	else
	{
		//error_or.get_val(traits::false_type{});
		std::cout << "The error_or value is: " << error_or.variable << " which is the variable type.\n";
	}

	constexpr bool s = true;

	// invoke_t < [&](bool b) {std::cout << "bool was:" << b; }, s > invoke_result{};
	std::cout << "\n";
	invoke_t<func, s> invoke_result_two{};
	std::cout << "invoke_t<func, s> invoke_result_two{}:\n";
	std::cout << "\n";
	std::cout << ".value\t=\t" << invoke_result_two.value;
	std::cout << "\n.type\t=\t";
	// auto typeid_result_type = typename invoke_result_two.type{};
	// std::cout << typeid(invoke_result_two.type);
	std::cout << "\n";
	std::string parse_str{ "///.parse.output" };
	parser(parse_str);
	
	std::cout << "\n";

	auto triple_invoke_lambda =
		[]() {
		return []()
		{
			return []() 
			{
				std::cout << "In a lambda.\n"; 
				return 42;
			};
		};
	};

	auto fortytwo = triple_invoke_lambda()()();

	// playing with constexpr if/ if constexpr
	std::string str_x = "fortytwo == 42;";
	std::string str_x_ = "fortytwo != 42;";
	std::cout << "\nThe value of \'fortytwo\' is: " << fortytwo << "\n";
	std::cout << "\n";
	auto one_true = VERIFY(fortytwo == 42, str_x); // notice the std::string_literals::s
	std::cout << "\n";
	auto none_true = VERIFY(fortytwo != 42, str_x_);
	// auto one_true_t = OneTrueLib::get<one_true>();
	// results in an error.
	std::cout << "\n";
	MUST(fortytwo == 42, str_x);
	int i_index = 0;
	std::cout << "Graphical ASCII: \n\n";
	for (auto code_point = 0x21; code_point <= 0x7E; code_point++)
	{
		if (i_index == 50)
		{
			std::cout << "\n";
			i_index = 0;
		}
		i_index += 5;
		std::cout << '(' << static_cast<char>(code_point) << ')' << ", ";
	}
	std::cout << "\n";

	my_container m_cont = 42;
	auto FirstLambda = [](auto& x) {x.__Data *= x.__Data; };
	auto SecondLambda = [](auto&& x) {x.__Data += 6; };

	std::cout << "\n";
	//     return *this / m_cont || return *this / m_cont.
	m_cont.and_then(FirstLambda).and_then(SecondLambda);
	std::cout << "m_cont.and_then(FirstLambda).and_then(SecondLambda):\n"
		<< "m_cont.d_m_i.__Data: " << m_cont.d_m_i.__Data << ".\n.";

	std::cout << "\nall(true, 5.6, 0, 9, 3.14159265358979323, 'c', false): ";
	std::cout << all(true, 5.6, 0, 9, 3.14159265358979323, 'c', false);

	std::cout << "\nall(5.2, true, 7, 9, 8.4, 0); : ";
	std::cout << all(5.2, true, 7, 9, 8.4, 0);

	all_<true, 5.2, 6, 9> a{};
	std::cout << "\n\nall_<true, 5.2, 6, 9> " << a.is();

	all_<true, 4, 42, false, 7> b{};
	std::cout << "\n\nall_<true, 4, 42, false, 7> " << b.is();

	std::cout << "\n\n";
}
