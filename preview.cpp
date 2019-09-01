#include <iostream>
#include <string>

#include <type_traits>
#include <utility>

// To Simplify
#define NoexceptInvoke noexcept(std::is_nothrow_invocable_v <Function, Argument>)

/*
 * the basic idea of this snippet as explained in this post https://www.bfilipek.com/2018/06/optional-examples-wall.html#monadic-extensions ,
 * is to be able to chain operations together by clever overloading of Bitwise operators left and right shift
 * even if the return type of the expression to be evaluated is void ,
 * the 'precedence' of the overloaded operators is the argument returned for the next production
 */

#define LIFT(Function)\
[](auto&&... args) noexcept(noexcept(  Function(std::forward <decltype(args)>(args)...)  )) -> decltype(Function(std::forward <decltype(args)>(args)...))\
{ return Function(std::forward <decltype(args)>(args)...); }

// about LIFT https://blog.tartanllama.xyz/passing-overload-sets/

// Accepts(Function >> Argument) returns Argument since right shift points to 'Argument'
template <class Function, class Argument, std::enable_if_t <std::is_invocable_v <Function, Argument>, int> = 0>
constexpr decltype(auto) operator>> (Function&& LHD, Argument&& RHD) NoexceptInvoke {
	if constexpr (std::is_invocable_r_v <void, Function, Argument>) {
		std::forward <Function>(LHD)(std::forward <Argument>(RHD));
		return std::forward <Argument>(RHD);
	}

	else {
		return std::forward <Function>(LHD)(std::forward <Argument>(RHD));
	}
}

// Accepts(Argument >> Function) returns Function since right shift points to 'Function'
template <class Argument, class Function, std::enable_if_t <std::is_invocable_v <Function, Argument>, int> = 0>
constexpr decltype(auto) operator>> (Argument&& LHD, Function&& RHD) NoexceptInvoke {
	if constexpr (std::is_invocable_r_v <void, Function, Argument>) {
		std::forward <Function>(RHD)(std::forward <Argument>(LHD));
		return std::forward <Function>(RHD);
	}

	else {
		return std::forward <Function>(RHD)(std::forward <Argument>(LHD));
	}
}

// Accepts(Function << Argument) returns Function since left shift points to 'Function'
template <class Function, class Argument, std::enable_if_t <std::is_invocable_v <Function, Argument>, int> = 0>
constexpr decltype(auto) operator<< (Function && LHD, Argument && RHD) NoexceptInvoke {
	if constexpr (std::is_invocable_r_v <void, Function, Argument>) {
		std::forward <Function>(LHD)(std::forward <Argument>(RHD));
		return std::forward <Function>(LHD);
	}

	else {
		return std::forward <Function>(LHD)(std::forward <Argument>(RHD));
	}
}

// Accepts(Argument << Function) returns Argument since left shift points to 'Argument'
template <class Argument, class Function, std::enable_if_t <std::is_invocable_v <Function, Argument>, int> = 0>
constexpr decltype(auto) operator<< (Argument && LHD, Function && RHD) NoexceptInvoke {
	if constexpr (std::is_invocable_r_v <void, Function, Argument>) {
		std::forward <Function>(RHD)(std::forward <Argument>(LHD));
		return std::forward <Argument>(LHD);
	}

	else {
		return std::forward <Function>(RHD)(std::forward <Argument>(LHD));
	}
}

/*


template <class FunctionL, class FunctionR, std::enable_if_t <std::is_invocable_v <FunctionL>, int> = 0>
constexpr decltype(auto) operator<< (FunctionL && LHD, FunctionR && RHD) noexcept(std::is_nothrow_invocable_v <FunctionL>) {
	if constexpr (std::is_invocable_r_v <void, FunctionL>) {
		std::forward <FunctionL>(LHD)();
		return std::forward <FunctionR>(RHD);
	}

	else {
		return std::forward <FunctionL>(LHD)();
	}
}


template <class FunctionL, class FunctionR, std::enable_if_t <std::is_invocable_v <FunctionR>, int> = 0>
constexpr decltype(auto) operator<< (FunctionL && LHD, FunctionR && RHD) noexcept(std::is_nothrow_invocable_v <FunctionR>) {
	if constexpr (std::is_invocable_r_v <void, FunctionR>) {
		std::forward <FunctionR>(RHD)();
		return std::forward <FunctionL>(LHD);
	}

	else {
		return std::forward <FunctionR>(RHD)();
	}
}


template <class FunctionL, class FunctionR, std::enable_if_t <std::is_invocable_v <FunctionL>, int> = 0>
constexpr decltype(auto) operator>> (FunctionL && LHD, FunctionR && RHD) noexcept(std::is_nothrow_invocable_v <FunctionL>) {
	if constexpr (std::is_invocable_r_v <void, FunctionL>) {
		std::forward <FunctionL>(LHD)();
		return std::forward <FunctionR>(RHD);
	}

	else {
		return std::forward <FunctionL>(LHD)();
	}
}


template <class FunctionL, class FunctionR, std::enable_if_t <std::is_invocable_v <FunctionR>, int> = 0>
constexpr decltype(auto) operator>> (FunctionL && LHD, FunctionR && RHD) noexcept(std::is_nothrow_invocable_v <FunctionR>) {
	if constexpr (std::is_invocable_r_v <void, FunctionR>) {
		std::forward <FunctionR>(RHD)();
		return std::forward <FunctionL>(LHD);
	}

	else {
		return std::forward <FunctionR>(RHD)();
	}
}

*/

int main() {
}
