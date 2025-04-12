#pragma once
#include "../pol/poly.hpp"
#include "interpolate.hpp"
#include <execution>
#include <utility>
#include <vector>
#include <algorithm>

namespace poly {
template <Arithmetic T>
class laplace final : public interpolate<T>
{
private:
    poly<T> getLagrange(const std::vector<std::pair<T, T>>& points, const size_t& idx) const
    {
        poly<T> result({T(1)});
        // std::println("Call to get Lang");
        for (size_t j = 0; j < points.size(); j++) {
            if (j == idx)[[unlikely]] {
                continue; // Skip the current index
            }

            // Build (x - x_j) term
            const poly<T> term({-points[j].first, T(1)}); // Represents (x - x_j)

            // Divide by (x_i - x_j)
            const T denominator = points[idx].first - points[j].first;

            // Multiply result by term/denominator
            result = result * (term / denominator);
        }

        return result;
    }

public:
    laplace() = default;

    poly<T> getInterpolationPolynom() const override
    {
        if (this->_points.empty()) {
            return poly<T>(); // Return empty polynomial if no points
        }

        std::vector<poly<T>> LagrangePolynomials;
        

        // std::vector<size_t> indices(this->_points.size());
        // std::iota(indices.begin(), indices.end(), 0);
        // LagrangePolynomials.resize(this->_points.size());
        // std::for_each(std::execution::par, indices.begin(), indices.end(),
        //     [this, &LagrangePolynomials](size_t i) {
        //         LagrangePolynomials[i] = getLagrange(this->_points, i);
        //     });
        
        LagrangePolynomials.reserve(this->_points.size());

        for (size_t i = 0; i < this->_points.size(); i++) {
            LagrangePolynomials.push_back(getLagrange(this->_points, i));
        }

        poly<T> p = LagrangePolynomials[0] * this->_points[0].second;
        for (size_t i = 1; i < LagrangePolynomials.size(); i++) {
            p = p + (LagrangePolynomials[i] * this->_points[i].second);
        }

        return p;
    }
};

} // namespace poly
