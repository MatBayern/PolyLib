#include "poly.hpp"
#include "../polyLib.hpp"
#include "formatPoly.hpp"
#include <complex>
#include <print>
#include <random>
// NOLINTBEGIN
int main() noexcept
{
    poly::poly<double> p(3); // Create a polynomial of degree 3
    poly::poly<int> p2({4, 7, 8}); // Represents 4 + 7x + 8x²
    poly::poly<int> p3({1, 2}); // Represents 4 + 2x
    poly::poly<double> p4({4, 7, 8});
    poly::poly<std::complex<double>> p5;
    poly::lagrange<double> l1;
    poly::newton<int> n1;

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
    std::println("{} ", p3 + p2);
    std::println("{} ", p4);
    p4.derivative();
    std::println("{} ", p4);

      // std::println("{} ", p.intregrate(2., 10.));

    return 0;
}
// NOLINTEND
