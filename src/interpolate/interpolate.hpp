#pragma once
#include "../pol/poly.hpp"
#include <utility>
#include <vector>

namespace poly {

template <Arithmetic T>
class Interpolate
{
protected:
    std::vector<std::pair<T, T>> _points;

public:
    Interpolate() = default;
    virtual ~Interpolate() = default;
    virtual Poly<T> getInterpolationPolynom() = 0;

    std::vector<std::pair<T, T>>& getPoints() const noexcept
    {
        return _points;
    }

    void addPoint(const T& x, const T& y)
    {
        _points.emplace_back(x, y);
    }
};
} // namespace poly