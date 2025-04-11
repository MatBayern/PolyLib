#pragma once
#include "../pol/poly.hpp"
#include <concepts>
#include <utility>
#include <vector>

namespace poly {

template <Arithmetic T>
class interpolate
{
protected:
    std::vector<std::pair<T, T>> _points;

public:
    interpolate() = default;
    virtual ~interpolate() = default;
    virtual poly<T> getInterpolationPolynom() const= 0;

    std::vector<std::pair<T, T>>& getPoints() noexcept
    {
        return _points;
    }

    void addPoint(const T& x, const T& y)
    {
        _points.emplace_back(x, y);
    }
};
} // namespace poly