# Chaining Expressions

Chaining Expressions is a set of (user-defined) operators << >> wich allows you to connect operations together ,

```cpp
#include <iostream>
#include <cassert>

#include <string>

#include "ExprChain.hpp"

std::string get_str();          // returns "123"
int to_int(std::string value);  // string to int conversion
int transform(int value);       // multiply by two
void c_out(int result);         // ouput

int main() {
    using namespace ExprChain;

    int integer = LIFT(get_str) >> LIFT(to_int) >> LIFT(transform) << LIFT(c_out);

    assert(integer == 246);
}
```

```
Output: 246
```
