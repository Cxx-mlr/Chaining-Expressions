# Chaining-Expressions

the basic idea of this snippet as explained in this post https://www.bfilipek.com/2018/06/optional-examples-wall.html#monadic-extensions ,
is to be able to chain operations together by clever overloading of Bitwise operators left and right shift even if the return type of the expression to be evaluated is void ,
the 'precedence' of the overloaded operators is the argument returned for the next production

```cpp
#include <iostream>
#include <string>

#include <fstream>

#include "ExprChain.hpp"


std::string read_file(const char* const path = "text.txt") {
    std::ifstream read(path);

    return std::string{ std::istreambuf_iterator <char>{read}, {} };
}


template <class type>
void c_out(const type & arg) { std::cout << arg; }



int to_int(const std::string &value) {
    return std::stoi(value) * 2;
}



int main()
{
    using namespace Cxx;
    
    int integer = std::string{"123"} << [](auto str) { std::cout << "converting: " << str << " to int ... "; } >> LIFT(to_int) << LIFT(c_out);
	
       // or
       //         LIFT(read_file)    << [](auto .. .
       // or
       //         read_file()        << [](auto .. .
       //
}
```
