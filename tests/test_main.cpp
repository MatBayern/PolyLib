#include "../src/polyLib.hpp"
#include <cmath>
#include <forward_list>
#include <gtest/gtest.h>
#include <vector>

TEST(PolynomialTestConstructor, empty)
{
    poly::Poly<double> p;
    ASSERT_EQ(p.getDegree(), 0);
}

TEST(PolynomialTestConstructor, VectorCopy)
{
    std::vector<double> coef = {1, 2, 3, 5};
    poly::Poly<double> p{coef};
    ASSERT_EQ(p.getDegree(), coef.size() - 1);
    for (size_t i = 0; i < coef.size(); i++) {
        ASSERT_DOUBLE_EQ(p[i], coef[i]);
        // ASSERT_NEAR
    }
}

TEST(PolynomialTestConstructor, VectorMove)
{
    std::vector<double> coef = {1, 2, 3, 5};
    std::vector<double> coefCopy{coef};

    poly::Poly<double> p{std::move(coefCopy)};
    ASSERT_EQ(p.getDegree(), coef.size() - 1);
    for (size_t i = 0; i < coef.size(); i++) {
        ASSERT_DOUBLE_EQ(p[i], coef[i]);
    }
}

TEST(PolynomialTestConstructor, Iterator)
{
    std::forward_list<double> coef = {1, 2, 3, 5};
    poly::Poly<double> p{coef.begin(), coef.end()};

    const size_t SIZE = std::distance(coef.begin(), coef.end());

    ASSERT_EQ(p.getDegree(), SIZE - 1);
    for (size_t i = 0; i < SIZE; i++) {
        ASSERT_DOUBLE_EQ(p[i], coef.front());
        coef.pop_front();
    }
}

TEST(PolynomialTestConstructor, initializerList)
{
    std::vector<double> coef = {1, 2, 3, 5};
    poly::Poly<double> p = {1, 2, 3, 5};

    ASSERT_EQ(p.getDegree(), 3);
    for (size_t i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(p[i], coef[i]);
    }
}

TEST(PolynomialTestOperator, Addition)
{
    poly::Poly<int> p1 = {1, 2, 3, 5};
    poly::Poly<int> p2 = {1, 2, 3, 5};

    poly::Poly<int> pResult = {2, 4, 6, 10};

    p1 = p1 + p2;

    ASSERT_EQ(p1.getDegree(), pResult.getDegree());
    for (size_t i = 0; i <= p1.getDegree(); i++) {
        ASSERT_EQ(p1[i], pResult[i]);
    }
}

TEST(PolynomialTestOperator, Addition2)
{
    poly::Poly<int> p1 = {1, 2, 3, 5};
    poly::Poly<int> p2 = {1, 2, 3};

    poly::Poly<int> pResult = {2, 4, 6, 5};

    p1 = p1 + p2;

    ASSERT_EQ(p1.getDegree(), pResult.getDegree());
    for (size_t i = 0; i <= p1.getDegree(); i++) {
        ASSERT_EQ(p1[i], pResult[i]);
    }
}

TEST(PolynomialTestOperator, Subtraktion)
{
    poly::Poly<int> p1 = {1, 2, 3, 5};
    poly::Poly<int> p2 = {2, 3, 4, 5};

    poly::Poly<int> pResult = {-1,- 1, -1};

    p1 = p1 - p2;

    ASSERT_EQ(p1.getDegree(), pResult.getDegree());
    for (size_t i = 0; i <= p1.getDegree(); i++) {
        ASSERT_EQ(p1[i], pResult[i]);
    }
}
TEST(PolynomialTestOperator, Subtraktion2)
{
    poly::Poly<int> p1 = {1, 2, 3, 5};
    poly::Poly<int> p2 = {1, 2, 3, 5};

    p1 = p1 - p2;

    ASSERT_EQ(p1.getDegree(), 0);
}

TEST(PolynomialTestOperator, Subtraktion3)
{
    poly::Poly<int> p1 = {1, 2, 3, 5};
    poly::Poly<int> p2 = {0, 2, 3, 5};

    p1 = p1 - p2;

    ASSERT_EQ(p1.getDegree(), 0);
    ASSERT_EQ(p1[0], 1);

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}