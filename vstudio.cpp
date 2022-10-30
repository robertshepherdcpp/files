#include<iostream> // std::cout
#include<chrono> // std::chrono
#include<string> // std::string, std::string_view
#include<vector> // std::vector
#include<utility> // std::pair

// just seeing how long std::puts and std::cout take.
// just carrying on from timur doumlers talk.

// using std::literals::chrono_literals;

namespace errors
{
	struct const_error{};
	struct generic_error {};
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

	//auto operator=(std::string& s)
	//{
	//	str = s;
	//}

	//simple_pod(std::string& s)
	//{
	//	str = s;
	//}

	//simple_pod()
	//{
	//	str = {};
	//}
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

// a kind of idea from ben deanes talk:


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
}
