#pragma once
#include "../pol/poly.hpp"
#include "interpolate.hpp"
#include <algorithm>
#include <execution>
#include <print>
#include <utility>
#include <vector>
namespace poly {
template <Arithmetic T>
class Newton final : public Interpolate<T>
{
private:
    // Members
    std::vector<T> _matrix{};
    std::size_t _size = 0;
    /**
     *
     *  Helper Functions
     *
     */
    void printMatrix() const
    {
        for (size_t i = 0; i < _size; i++) {
            for (size_t j = 0; j < _size; j++) {
                std::print("{} ", _matrix[i + (_size * j)]);
            }
            std::println("");
        }
    }
    constexpr T divideDifference(const T& ci1, const T& ci, const T& xik, const T& xi) const noexcept
    {
        return (ci1 - ci) / (xik - xi);
    }

    /**
     *
     * @short Calculate divided differences
     */
    std::vector<T> returnCoefficients()
    {
        const std::size_t N = this->_points.size();
        std::vector<T> coefficients;
        coefficients.reserve(N);

        coefficients.push_back(_matrix[0]); // First value, f(x0)

        // Calculate divided differences
        for (size_t i = 1; i < N; ++i) {
            for (size_t j = 0; j < N - i; ++j) {
                size_t currentIdx = j + i * N;
                size_t prevRowIdx = j + (i - 1) * N;

                const T& xj = this->_points[j].first;
                const T& xji = this->_points[j + i].first;
                const T& a = _matrix[prevRowIdx];
                const T& b = _matrix[prevRowIdx + 1];

                _matrix[currentIdx] = divideDifference(b, a, xji, xj);
            }
            coefficients.push_back(_matrix[i * N]);
        }
        return coefficients;
    }

public:
    Newton() = default;
    /**
     * @short This build a newton polynomial from the given points. Watchout this assumes that the points are only increades and not modiyfed!
     *  if you modify any points you have to reconstruct a new Object!
     */
    Poly<T> getInterpolationPolynom() override
    {
        
        if (this->_points.size())
        {
            return Poly<T>{}; // No points were added
        }
        // Incase new points are added
        // we need to resize the matrix
        if (_size != this->_points.size()) {
            std::vector<T> newMatrix(this->_points.size() * this->_points.size(), T{});

            for (size_t i = 0; i < this->_points.size(); i++) {
                for (size_t j = 0; j < this->_points.size(); j++) {
                    if (i < _size && j < _size) {
                        // Copy existing matrix values
                        newMatrix[j + (this->_points.size() * i)] = _matrix[j + (_size * i)];
                    } else if (i == 0) {
                        // Initialize first row with y values
                        newMatrix[j] = this->_points[j].second;
                    }
                }
            }

            _matrix = std::move(newMatrix);
            _size = this->_points.size();
        }

        const std::vector<T> COEFFICIENTS = returnCoefficients();
        /**
         *  Construct the polynomial using the coefficients
         */
        Poly<T> result({COEFFICIENTS[0]});
        for (std::size_t i = 1; i < _size; ++i) {
            Poly<T> term({T(1)});
            for (std::size_t j = 0; j < i; ++j) {
                term = term * Poly<T>({-this->_points[j].first, T(1)});
            }
            result = result + (term * COEFFICIENTS[i]);
        }

        return result;
    }
};

} // namespace poly
