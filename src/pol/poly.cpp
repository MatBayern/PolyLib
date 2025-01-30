#include "poly.hpp"
#include <print>
int main(void)
{
    poly::poly<double> p(3);
    poly::poly<double> p2(3);

    for (size_t i = 0; i < p.getDegree() + 1; i++)
    {
        p[i] = i;
        p2[i] = i;

    }
    p = p - p2;
    for (size_t i = 0; i < p.getDegree() + 1; i++)
    {
        std::println("{} ", p[i]);
    }

    return 0;
}
