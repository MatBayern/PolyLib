#pragma once
#include "../pol/poly.hpp"
#include "interpolate.hpp"
#include <algorithm>
#include <execution>
#include <utility>
#include <vector>
namespace poly {
template <Arithmetic T>
class Newton final : public Interpolate<T>
{
private:
    std::vector<T> _matrix;
    std::size_t _size;

    constexpr T divideDiffrence(const T& ci1, const T& ci, const T& xik, const T& xi) const noexcept
    {
        return (ci1 - ci) / (xik - xi);
    }
    std::vector<T> returnCoeffiecents() const
    {
        std::vector<T> coefficents;
        coefficents.resize(this->_points.size());

        std::vector<T> scratch;
        scratch.reserve(this->_points.size());

        for (const auto& point : this->_points) {
            scratch.push_back(point.second);
        }

        for (size_t i = 1; i < this->_points.size(); i++) {
            for (size_t j = 0; j < this->_points.size() - i; j++) {
                scratch[j] = divideDiffrence(scratch[j + 1], scratch[j], this->_points[i + j].first, this->_points[j].first);
            }
            coefficents[i] = scratch[0];
        }
        return coefficents;
    }

public:
    Newton() = default;
    Poly<T> getInterpolationPolynom() const override
    {
        if (_size != this->_points.size()) {
            /* code */
        }

        Poly<T> p(returnCoeffiecents());

        return p;
    }
};

} // namespace poly
