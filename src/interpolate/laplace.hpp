#pragma once
#include "../pol/poly.hpp"
#include "interpolate.hpp"

namespace poly {
template <Arithmetic T>
class laplace final : public interpolate<T>
{
private:
    poly<T> getLagrange(const std::vector<std::pair<T, T>>& points, const size_t& idx) const
    {
        poly<T> result({T(1)});

        for (size_t j = 0; j < points.size(); j++) {
            if (j == idx) {
                continue; // Skip the current index
            }

            // Build (x - x_j) term
            poly<T> term({-points[j].first, T(1)}); // Represents (x - x_j)

            // Divide by (x_i - x_j)
            T denominator = points[idx].first - points[j].first;

            // Multiply result by term/denominator
            result = result * (term / denominator);
        }

        return result;
    }

public:
    laplace() {};

    poly<T> getInterpolationPolynom() const override
    {
        if (this->_points.empty()) {
            return poly<T>(); // Return empty polynomial if no points
        }

        std::vector<poly<T>> LagrangePolynomials;
        std::println("anfang von langrage polys");
        for (size_t i = 0; i < this->_points.size(); i++) {
            auto tmpP = getLagrange(this->_points, i);
            LagrangePolynomials.push_back(std::move(tmpP));
        }
        std::println("Fertig mit langrage polys");
        poly<T> p = LagrangePolynomials[0] * this->_points[0].second;
        for (size_t i = 1; i < LagrangePolynomials.size(); i++) {
            p = p + (LagrangePolynomials[i] * this->_points[i].second);
        }
        std::println("Fertig mit fertig mit summe polys");

        return p;
    }
};

} // namespace poly
