#ifndef ExprChain_hpp
#define ExprChain_hpp

#define CXX_BEGIN namespace Cxx {
#define CXX_END }

CXX_BEGIN
#include <type_traits>
#include <utility>

// To Simplify
#define NoexceptInvoke noexcept(std::is_nothrow_invocable_v <Function, Argument>)


#define LIFT(Function)\
[](auto&&... args) noexcept(noexcept(  Function(std::forward <decltype(args)>(args)...)  )) -> decltype(Function(std::forward <decltype(args)>(args)...))\
{ return Function(std::forward <decltype(args)>(args)...); }

// about LIFT https://blog.tartanllama.xyz/passing-overload-sets/

#define OPT(Function, op)\
[](auto&&... args) -> decltype(  ((Function op std::forward <decltype(args)>(args)), ...)  )\
{ return ((Function op std::forward <decltype(args)>(args)), ...); }

 // Accepts(Function >> Argument) returns Argument since right shift points to 'Argument'
	template <class Function, class Argument, std::enable_if_t <std::is_invocable_v <Function, Argument>, int> = 0>
constexpr decltype(auto) operator>> (Function && LHD, Argument && RHD) NoexceptInvoke {
	if constexpr (std::is_invocable_r_v <void, Function, Argument>) {
		std::forward <Function>(LHD)(RHD);
		return std::forward <Argument>(RHD);
	}

	else {
		return std::forward <Function>(LHD)(std::forward <Argument>(RHD));
	}
}

// Accepts(Argument >> Function) returns Function since right shift points to 'Function'
template <class Argument, class Function, std::enable_if_t <std::is_invocable_v <Function, Argument>, int> = 0>
constexpr decltype(auto) operator>> (Argument && LHD, Function && RHD) NoexceptInvoke {
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, Argument>>) {
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
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, Argument>>) {
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
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, Argument>>) {
		std::forward <Function>(RHD)(LHD);
		return std::forward <Argument>(LHD);
	}

	else {
		return std::forward <Function>(RHD)(std::forward <Argument>(LHD));
	}
}

/////////////////////////////////

template <class FunctionL, class FunctionR, std::enable_if_t <std::is_invocable_v <FunctionL>&& std::is_invocable_v <FunctionR, std::invoke_result_t <FunctionL>>, int> = 0>
constexpr decltype(auto) operator>> (FunctionL && LHD, FunctionR && RHD) noexcept(std::is_nothrow_invocable_v <FunctionL> && std::is_nothrow_invocable_v <FunctionR, std::invoke_result_t <FunctionL>>) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <FunctionR, std::invoke_result_t <FunctionL>>>) {
		std::forward <FunctionR>(RHD)(std::forward <FunctionL>(LHD)());
		return std::forward <FunctionR>(RHD);
	}

	else {
		return std::forward <FunctionR>(RHD)(std::forward <FunctionL>(LHD));
	}
}

template <class FunctionL, class FunctionR, std::enable_if_t <std::is_invocable_v <FunctionR>&& std::is_invocable_v <FunctionL, std::invoke_result_t <FunctionR>>, int> = 0>
constexpr decltype(auto) operator>> (FunctionL && LHD, FunctionR && RHD) noexcept(std::is_nothrow_invocable_v <FunctionR> && std::is_nothrow_invocable_v <FunctionL, std::invoke_result_t <FunctionR>>) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <FunctionR, std::invoke_result_t <FunctionL>>>) {
		std::forward <FunctionL>(LHD)(std::forward <FunctionR>(RHD)());
		return std::forward <FunctionR>(RHD);
	}

	else {
		return std::forward <FunctionL>(LHD)(std::forward <FunctionR>(RHD)());
	}
}

template <class FunctionL, class FunctionR, std::enable_if_t <std::is_invocable_v <FunctionL>&& std::is_invocable_v <FunctionR, std::invoke_result_t <FunctionL>>, int> = 0>
constexpr decltype(auto) operator<< (FunctionL && LHD, FunctionR && RHD) noexcept(std::is_nothrow_invocable_v <FunctionL> && std::is_nothrow_invocable_v <FunctionR, std::invoke_result_t <FunctionL>>) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <FunctionR, std::invoke_result_t <FunctionL>>>) {
		std::forward <FunctionR>(RHD)(std::forward <FunctionL>(LHD)());
		return std::forward <FunctionL>(LHD);
	}

	else {
		return std::forward <FunctionR>(RHD)(std::forward <FunctionL>(LHD));
	}
}

template <class FunctionL, class FunctionR, std::enable_if_t <std::is_invocable_v <FunctionR>&& std::is_invocable_v <FunctionL, std::invoke_result_t <FunctionR>>, int> = 0>
constexpr decltype(auto) operator<< (FunctionL && LHD, FunctionR && RHD) noexcept(std::is_nothrow_invocable_v <FunctionR> && std::is_nothrow_invocable_v <FunctionL, std::invoke_result_t <FunctionR>>) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <FunctionR, std::invoke_result_t <FunctionL>>>) {
		std::forward <FunctionL>(LHD)(std::forward <FunctionR>(RHD)());
		return std::forward <FunctionL>(LHD);
	}

	else {
		return std::forward <FunctionL>(LHD)(std::forward <FunctionR>(RHD)());
	}
}

/////////////////////////////////
CXX_END

#endif
