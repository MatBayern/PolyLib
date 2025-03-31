#include "poly.hpp"
#include "formatPoly.hpp"
#include <print>
#include <complex>
int main(void)
{
    poly::poly<double> p(3);
    poly::poly<int> p2(3);
    poly::poly<int> p3;

     
    for (size_t i = 0; i < p.getDegree() + 1; i++)
    {
        p[i] = i;
        p2[i] = i;

    }
    // p = p * p2;
    for (size_t i = 0; i < p.getDegree() +1 ; i++)
    {
        
    }
    std::println("{} ", p);

    return 0;
}
