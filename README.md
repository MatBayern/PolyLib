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
poly::poly<int> p3({1, 2}); // Represents 4 + 2x
poly::poly<double> p4({4, 7, 8});
poly::poly<std::complex<double>> p5; // Zero polynomial
// Utils
std::println("{} ", p2); // Will print 4 + 9x + 8x^2
p2 + p3 // 5 + 9x + 8x²
p3 == p3 // true
p2 * p3 // 4 + 15x + 22x^2 + 16x^3 
4 * p3 // 16 + 8x
p2 == p4 // false because the types are diffrent!
p2[1] // returns 7
p2[0] // returns 4
p3(1) // evaluates to 6 using Horner's scheme
p4.derivative(); // evaluates to 7 + 16x
// Constructions
std::list<double> l1 = {4, 7, 8};
poly::Poly<double> p5{v1.begin(), v1.end()}; // at least a std::forward_iterator is required

std::vector<double> v1 = {4, 7, 8};
poly::Poly<double> p6{v1}; // copys the vector
poly::Poly<double> p7{std::move(v1)}; // moves the vector 
```
Check out the `poly.cpp` file for more examples.
Have fun! 🎉