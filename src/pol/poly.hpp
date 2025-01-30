#pragma once
#include <cmath>
#include <vector>
#include <utility>

namespace poly
{
    template <typename T>
    class poly
    {
        // Check if necessary operators are defined for T
        static_assert(std::is_same<decltype(std::declval<T>() + std::declval<T>()), T>::value, "T must support operator+");
        static_assert(std::is_same<decltype(std::declval<T>() - std::declval<T>()), T>::value, "T must support operator-");
        static_assert(std::is_same<decltype(std::declval<T>() * std::declval<T>()), T>::value, "T must support operator*");

    private:
        size_t _degree;
        std::vector<T> _coefficients;

    public:
        poly(/* args */);
        ~poly();

        T &operator[](size_t index)
        {
            if (index >= _degree + 1)
            {
                throw std::runtime_error("invalid access");
            }
            return _coeff[index];
        }

        T operator[](size_t index) const
        {
            if (index >= _degree + 1)
            {
                throw std::runtime_error("invalid access");
            }
            return _coeff[index];
        }

        T operator()(const T &x) const
        {
            T result = _coeff[_degree];
            for (int i = _degree - 1; i >= 0; i--)
            {
                result = result * x + _coeff[i];
            }
            return result;
        }
    };
} // namespace poly
