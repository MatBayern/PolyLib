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
public:
    Newton() = default;
    Poly<T> getInterpolationPolynom() const override
    {
        return Poly<T>();
    }
};

} // namespace poly
