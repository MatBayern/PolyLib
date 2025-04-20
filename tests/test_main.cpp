#include "../src/polyLib.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

TEST(PolynomialTest, simpleTest)
{
    poly::Poly<double> p;
    ASSERT_EQ(p.getDegree(), 0);
}

TEST(PolynomialTest, checkCoefficent)
{
    std::vector<double> coef = {1, 2, 3, 5};
    poly::Poly<double> p{coef};
    ASSERT_EQ(p.getDegree(), coef.size() - 1);
    for (size_t i = 0; i < coef.size(); i++)
    {
        ASSERT_DOUBLE_EQ(p[i], coef[i]);
    }
    
}
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}