# Chaining Expressions

Chaining Expressions is a set of (user-defined) operators << >> wich allows you to connect operations together ,

```cpp
#include <iostream>
#include <cassert>

#include <string>

#include "ExprChain.hpp"

std::string get_str()         { return "123";            }
int to_int(std::string value) { return std::stoi(value); }
int transform(int value)      { return value * 2;        }
void c_out(int result)        { std::cout << result;     }

int main() {
    using namespace ExprChain;

    int integer = LIFT(get_str) >> LIFT(to_int) >> LIFT(transform) << LIFT(c_out);

    assert(integer == 246);
}
```

```
Output: 246
```
