
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
auto operator>> (Function && function, Argument && argument) {
	function(argument);

	return argument;
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, Argument>, int > = 0>
auto operator>> (Argument && argument, Function && function) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, Argument>>) {
		function(argument);

		return function;
	}

	else {
		return function(argument);
	}
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, std::invoke_result_t <Argument>> && std::is_same_v <void, std::invoke_result_t <Function, std::invoke_result_t <Argument>>> , int > = 0>
auto operator>> (Function && function, Argument && argument) {
	function(argument());

	return argument;
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, std::invoke_result_t <Argument>>, int > = 0>
auto operator>> (Argument && argument, Function && function) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, std::invoke_result_t <Argument>>>) {
		function(argument());

		return function;
	}

	else {
		return function(argument());
	}
}


///////////////////////////////////////////////

///////////////////////////////////////////////


template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, Argument>, int > = 0>
auto operator<< (Function && function, Argument && argument) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, Argument>>) {
		function(argument);

		return function;
	}

	else {
		return function(argument);
	}
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, Argument> && std::is_same_v <void, std::invoke_result_t <Function, Argument>>, int > = 0>
auto operator<< (Argument && argument, Function && function) {
	function(argument);

	return argument;
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, std::invoke_result_t <Argument>>, int > = 0>
auto operator<< (Function && function, Argument && argument) {
	if constexpr (std::is_same_v <void, std::invoke_result_t <Function, std::invoke_result_t <Argument>>>) {
		function(argument());

		return function;
	}

	else {
		return function(argument());
	}
}

template <class Function, class Argument, std::enable_if_t < std::is_invocable_v <Function, std::invoke_result_t <Argument>> && std::is_same_v <void, std::invoke_result_t <Function, std::invoke_result_t <Argument>>>, int > = 0>
auto operator<< (Argument && argument, Function && function) {
	function(argument());

	return argument;
}


///////////////////////////////////////////////

#define LIFT(Function)\
[](auto&&... args) noexcept(noexcept( Function(  std::forward <decltype(args)>(args)...  ) )) -> decltype( Function( std::forward <decltype(args)>(args)...) )\
{ return Function(  std::forward <decltype(args)>(args)...  ); }

// about LIFT https://blog.tartanllama.xyz/passing-overload-sets/

#define OPT(Function, Opt) [](auto&& ... args) -> decltype(((std::cout << args), ...)) { return ((Function Opt args), ...); }

EXPRCHAIN_END

#endif // ExprChain_hpp
