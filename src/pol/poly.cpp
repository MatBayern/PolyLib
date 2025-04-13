#include "poly.hpp"
#include "../polyLib.hpp"
#include "formatPoly.hpp"
#include <complex>
#include <print>
#include <random>
// NOLINTBEGIN
int main() noexcept
{
    poly::Poly<double> p(3); // Create a polynomial of degree 3
    poly::Poly<int> p2({4, 7, 8}); // Represents 4 + 7x + 8x²
    poly::Poly<int> p3({1, 2}); // Represents 4 + 2x
    poly::Poly<double> p4({4, 7, 8});

    poly::Lagrange<double> l1;
    poly::Newton<int> n1;

    std::mt19937 gen(42); // Mersenne Twister random number engine

    for (size_t i = 0; i < 1000; i++) {
        l1.addPoint(gen(), gen());
    }
    n1.addPoint(1, 1);
    std::println("Added Points");
    // auto p4 = l1.getInterpolationPolynom();

    // p = p * p2;
    for (size_t i = 0; i < p.getDegree() + 1; i++) {
    }
    std::println("{} ", p4);

    std::vector<double> v1 = {4, 7, 8};
    poly::Poly<double> p5{std::move(v1)};


    std::println("{} ", p5);

    return 0;
}
// NOLINTEND
