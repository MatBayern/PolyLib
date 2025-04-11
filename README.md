# PolyLib

A simple and generic C++23 polynomial library.

## Usage

Just include the `polyLib.hpp` header file in your project:

```cpp
#include "polyLib.hpp"
```
## Requirements

PolyLib is designed to be as generic as possible. However, your coefficient type must support the following operators:
- `+`
- `*`
- `-` (including unary `-`)
- `/`
- `==`
Additionally, your type must provide two constructors:
```cpp
A{}     // should yield the additive identity (typically 0)
A{1}    // should yield the multiplicative identity (typically 1)

```
## Examples

```C++
poly::poly<double> p(3); // Create a polynomial of degree 3
poly::poly<int> p2({4, 7, 8}); // Represents 4 + 7x + 8x²
poly::poly<std::complex<double>> p3; // Zero polynomial
// Utils
std::println("{} ", p2); // Will print 4 + 7x + 8x^2 

```
Check out the poly.cpp file for more examples.
Have fun! 🎉