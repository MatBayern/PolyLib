#include "../polyLib.hpp"
#include "formatPoly.hpp"
#include "poly.hpp"
#include <complex>
#include <list>
#include <print>
#include <random>

// NOLINTBEGIN
int main()
{
    poly::Poly<double> p(3); // Create a polynomial of degree 3
    poly::Poly<int> p2({4, 7, 8}); // Represents 4 + 7x + 8x²
    poly::Poly<int> p3({1, 2}); // Represents 4 + 2x
    poly::Poly<double> p4({4, 7, 8});

    poly::Lagrange<double> l1;
    poly::Newton<double> n1;

    std::mt19937 gen(42); // Mersenne Twister random number engine

    // for (size_t i = 0; i < 1000; i++) {
    //     const auto x  = gen();
    //     const auto y = gen();
    //     l1.addPoint(x,y);
    //     n1.addPoint(x,y);

    // }
    n1.addPoint(1, 0);
    n1.addPoint(2, 2);
    n1.addPoint(3, 5);

    l1.addPoint(1, 0);
    l1.addPoint(2, 2);
    l1.addPoint(3, 5);
    std::println("Added Points");
    // auto p4 = l1.getInterpolationPolynom();

    // p = p * p2;
    for (size_t i = 0; i < p.getDegree() + 1; i++) {
    }
    // std::println("{} ", n1.getInterpolationPolynom());
    // std::println("{} ", l1.getInterpolationPolynom());

    // std::println("{} ", n1.getInterpolationPolynom());
    //  std::println("{} ", l1.getInterpolationPolynom());
    //  l1.addPoint(4, 100);
    //  std::println("{} ", l1.getInterpolationPolynom());

    std::println("{} ", n1.getInterpolationPolynom());
    // n1.addPoint(4, 100);
    // std::println("{} ", n1.getInterpolationPolynom());

    std::list<double> list1 = {4, 7, 8, 2};
    poly::Poly<double> p5{list1.begin(), list1.end()}; // at least a std::forward_iterator is required

    std::println("{} ", p5);
    p5.derivative();
    std::println("{} ", p5);

    return 0;
}

// NOLINTEND
