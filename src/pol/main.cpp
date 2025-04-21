#include "../polyLib.hpp"
#include "formatPoly.hpp"
#include "poly.hpp"
#include <chrono>
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

    for (size_t i = 0; i < 1000; i++) {
        const auto x = gen();
        const auto y = gen();
        l1.addPoint(x, y);
        n1.addPoint(x, y);
    }
    // n1.addPoint(1, 0);
    // n1.addPoint(2, 2);
    // n1.addPoint(3, 5);

    // l1.addPoint(1, 0);
    // l1.addPoint(2, 2);
    // l1.addPoint(3, 5);
    std::println("Added Points");
    // auto p4 = l1.getInterpolationPolynom();
    auto start1 = std::chrono::high_resolution_clock::now();
    l1.getInterpolationPolynom();
    auto stop1 = std::chrono::high_resolution_clock::now();

    std::println("Took {}", std::chrono::duration_cast<std::chrono::seconds>(stop1 - start1));
    l1.setExecutionMode(true);
    auto start2 = std::chrono::high_resolution_clock::now();

    l1.getInterpolationPolynom();

    auto stop2 = std::chrono::high_resolution_clock::now();
    std::println("Took {}", std::chrono::duration_cast<std::chrono::seconds>(stop2 - start2));

    auto start3 = std::chrono::high_resolution_clock::now();
    n1.getInterpolationPolynom();
    auto stop3 = std::chrono::high_resolution_clock::now();
    std::println("Took {}", std::chrono::duration_cast<std::chrono::seconds>(stop3 - start3));

    auto start4 = std::chrono::high_resolution_clock::now();
    n1.getInterpolationPolynom();
    auto stop4 = std::chrono::high_resolution_clock::now();
    std::println("Took {}", std::chrono::duration_cast<std::chrono::seconds>(stop4 - start4));

    return 0;
}

// NOLINTEND
