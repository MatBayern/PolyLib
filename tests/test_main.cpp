#include "../src/polyLib.hpp"
#include <cmath>
#include <gtest/gtest.h>

TEST(PolynomialTest, simpleTest)
{
    poly::Poly<double> p;
    ASSERT_EQ(p.getDegree(), 0);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}