#pragma once
#include "../pol/poly.hpp"
#include "interpolate.hpp"
#include <algorithm>
#include <execution>
#include <utility>
#include <vector>

namespace poly {
template <Arithmetic T>
class lagrange final : public interpolate<T>
{
private:
    /**
     *  @short Helper function for calucating a lagrange polynominal for the given index.
     *  @param[in] points A Vector if all the points which are used to interpolate
     *  @param[in] index The index which point we want create the lagrange polynominal
     *  @param[out] poly The polynominal for the given index
     */
    poly<T> getLagrange(const std::vector<std::pair<T, T>>& points, const size_t& idx) const
    {
        poly<T> result({T(1)});
        // std::println("Call to get Lang");
        for (size_t j = 0; j < points.size(); j++) {
            if (j == idx) [[unlikely]] {
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
    lagrange() = default;
    /**
     *
     *  This will return the Interpolation Polynom for the given points using lagrange method.
     *  @param[out] polynom The interpolation polynom for the Type T
     */
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
            LagrangePolynomials.push_back(getLagrange(this->_points, i)); // get Lagrange Polynomials for every index
        }

        poly<T> p = LagrangePolynomials[0] * this->_points[0].second;
        for (size_t i = 1; i < LagrangePolynomials.size(); i++) {
            p = p + (LagrangePolynomials[i] * this->_points[i].second); // Multiply them togehter to create the resulting polynomianal
        }

        return p;
    }
};

} // namespace poly
