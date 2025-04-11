#pragma once
#include "../pol/poly.hpp"
#include "interpolate.hpp"
#include <algorithm>
#include <execution>
#include <utility>
#include <vector>
namespace poly {
template <Arithmetic T>
class newton final : public interpolate<T>
{
private:
public:
    newton() = default;
    poly<T> getInterpolationPolynom() const override
    {
        return poly<T>();
    }
};

} // namespace poly
