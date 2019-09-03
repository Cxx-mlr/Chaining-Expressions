
/*
 * the basic idea of this snippet as explained in this post https://www.bfilipek.com/2018/06/optional-examples-wall.html#monadic-extensions ,
 * is to be able to chain operations together by clever overloading of Bitwise operators left and right shift
 * even if the return type of the expression to be evaluated is void ,
 * the 'precedence' of the overloaded operators is the argument returned for the next production
 */


#ifndef ExprChain_hpp
#define ExprChain_hpp

#include <type_traits>
#include <utility>

#define EXPRCHAIN_BEGIN namespace ExprChain {
#define EXPRCHAIN_END }


EXPRCHAIN_BEGIN
///////////////////////////////////////////////

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, Argument> && std::is_same_v <void, std::invoke_result_t <Function, Argument>>, int > = 0>
decltype(auto) operator>> (Function && function, Argument && argument) noexcept(std::is_nothrow_invocable_v <Function, Argument>) {
	std::forward <Function>(function)(argument);

	return std::forward <Argument>(argument);
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, Argument>, int > = 0>
decltype(auto) operator>> (Argument && argument, Function && function) noexcept(std::is_nothrow_invocable_v <Function, Argument>) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, Argument>>) {
		std::forward <Function>(function)(std::forward <Argument>(argument));

		return std::forward <Function>(function);
	}

	else {
		return std::forward <Function>(function)(std::forward <Argument>(argument));
	}
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, std::invoke_result_t <Argument>> && std::is_same_v <void, std::invoke_result_t <Function, std::invoke_result_t <Argument>>>, int > = 0>
decltype(auto) operator>> (Function && function, Argument && argument) noexcept(std::is_nothrow_invocable_v <Function, std::invoke_result_t <Argument>>) {
	std::forward <Function>(function)(std::forward <Argument>(argument)());

	return std::forward <Argument>(argument);
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, std::invoke_result_t <Argument>>, int > = 0>
decltype(auto) operator>> (Argument && argument, Function && function) noexcept(std::is_nothrow_invocable_v <Function, std::invoke_result_t <Argument>>) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, std::invoke_result_t <Argument>>>) {
		std::forward <Function>(function)(std::forward <Argument>(argument)());

		return std::forward <Function>(function);
	}

	else {
		return std::forward <Function>(function)(std::forward <Argument>(argument)());
	}
}


///////////////////////////////////////////////

///////////////////////////////////////////////


template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, Argument>, int > = 0>
decltype(auto) operator<< (Function && function, Argument && argument) noexcept(std::is_nothrow_invocable_v <Function, Argument>) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, Argument>>) {
		std::forward <Function>(function)(std::forward <Argument>(argument));

		return std::forward <Function>(function);
	}

	else {
		return std::forward <Function>(function)(std::forward <Argument>(argument));
	}
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, Argument> && std::is_same_v <void, std::invoke_result_t <Function, Argument>>, int > = 0>
decltype(auto) operator<< (Argument && argument, Function && function) noexcept(std::is_nothrow_invocable_v <Function, Argument>) {
	std::forward <Function>(function)(argument);

	return std::forward <Argument>(argument);
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, std::invoke_result_t <Argument>>, int > = 0>
decltype(auto) operator<< (Function && function, Argument && argument) noexcept(std::is_nothrow_invocable_v <Function, std::invoke_result_t <Argument>>) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, std::invoke_result_t <Argument>>>) {
		std::forward <Function>(function)(std::forward <Argument>(argument)());

		return std::forward <Function>(function);
	}

	else {
		return std::forward <Function>(function)(std::forward <Argument>(argument)());
	}
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, std::invoke_result_t <Argument>> && std::is_same_v <void, std::invoke_result_t <Function, std::invoke_result_t <Argument>>>, int > = 0>
decltype(auto) operator<< (Argument && argument, Function && function) noexcept(std::is_nothrow_invocable_v <Function, std::invoke_result_t <Argument>>) {
	std::forward <Function>(function)(std::forward <Argument>(argument)());

	return std::forward <Argument>(argument);
}


///////////////////////////////////////////////

#define LIFT(Function)\
[](auto&&... args) noexcept(noexcept( Function(  std::forward <decltype(args)>(args)...  ) )) -> decltype( Function( std::forward <decltype(args)>(args)...) )\
{ return Function(  std::forward <decltype(args)>(args)...  ); }

// about LIFT https://blog.tartanllama.xyz/passing-overload-sets/

#ifdef _MSC_VER

#define OPT(Function, Opt)\
[](auto&& ... args) -> decltype(((Function Opt std::forward <decltype(args)>(args)), ...))\
{ return ((Function Opt std::forward <decltype(args)>(args)), ...); }

#else

#define OPT(Function, Opt)\
[](auto&& ... args) noexcept(noexcept( ((Function Opt std::forward <decltype(args)>(args)), ...) )) -> decltype(((Function Opt std::forward <decltype(args)>(args)), ...))\
{ return ((Function Opt std::forward <decltype(args)>(args)), ...); }

#endif

EXPRCHAIN_END

#endif // ExprChain_hpp
