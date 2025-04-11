#include "poly.hpp"
#include "../interpolate/lagrange.hpp"
#include "formatPoly.hpp"
#include <complex>
#include <print>
#include <random>

int main(void)
{
    poly::poly<double> p(3);
    poly::poly<int> p2({4, 7, 8});
    poly::poly<int> p3;
    poly::laplace<double> l1;

    std::mt19937 gen(42); // Mersenne Twister random number engine

    for (size_t i = 0; i < 1000; i++) {
        l1.addPoint(gen(), gen());
    }
    std::println("Added Points");
    auto p4 = l1.getInterpolationPolynom();

    // p = p * p2;
    for (size_t i = 0; i < p.getDegree() + 1; i++) {
    }
    std::println("{} ", p4);

    // std::println("{} ", p.intregrate(2., 10.));

    return 0;
}
