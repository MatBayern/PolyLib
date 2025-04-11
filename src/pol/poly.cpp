#include "poly.hpp"
#include <complex>
#include <print>
#include "formatPoly.hpp"
#include "../interpolate/laplace.hpp"
int main(void)
{
    poly::poly<double> p(3);
    poly::poly<int> p2({4,7,8});
    poly::poly<int> p3;
    poly::laplace<double> l1;


    l1.addPoint(0,2);
    l1.addPoint(2,0);
    l1.addPoint(4,-1);

    auto p4 = l1.getInterpolationPolynom();

    // p = p * p2;
    for (size_t i = 0; i < p.getDegree() + 1; i++) {
    }
    std::println("{} ", p4);

    // std::println("{} ", p.intregrate(2., 10.));

    return 0;
}
