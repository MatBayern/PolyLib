#pragma once
#include <cmath>
#include <vector>
#include <utility>
#include <stdexcept>
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
        std::vector<T> _coeff;

    public:
        poly(size_t degree) : _degree(degree), _coeff(degree + 1) {};
        ~poly() = default;

        T getDegree() const
        {
            return _degree;
        }
        /**
         *
         *  Operator Overloading
         *
         */

        T &operator[](const size_t &index)
        {
            if (index >= _degree + 1)
            {
                throw std::runtime_error("invalid access");
            }
            return _coeff[index];
        }

        T operator[](const size_t &index) const
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

        poly<T> operator+(const poly<T> &other) const
        {
            poly<T> result(std::max(_degree, other._degree));
            for (size_t i = 0; i <= std::max(_degree, other._degree); i++)
            {
                result[i] = (i <= _degree ? _coeff[i] : 0) + (i <= other._degree ? other._coeff[i] : 0);
            }
            return result;
        }

        poly<T> operator-(const poly<T> &other) const
        {
            return *this + (-other);
        }

        poly<T> operator*(const poly<T> &other) const
        {
            poly<T> result(_degree + other._degree);
            for (size_t i = 0; i <= _degree; i++)
            {
                for (size_t j = 0; j <= other.getDegree(); j++)
                {
                    T tmp = _coeff[i] * other[j];
                    result[i + j] = result[i + j] + tmp;
                }
            }
            return result;
        }

        poly<T> operator-() const
        {
            poly<T> result(_degree);
            for (size_t i = 0; i <= _degree; i++)
            {
                result[i] = -_coeff[i];
            }
            return result;
        }

        template <typename U>
        bool operator==(const poly<U> /**/) const
        {
            return false;
        }

        bool operator==(const poly<T> &other) const
        {
            if (_degree != other.getDegree())
            {
                return false;
            }
            for (size_t i = 0; i <= _degree; i++)
            {
                if (_coeff[i] != other[i])
                {
                    return false;
                }
            }
            return true;
        }
    };
} // namespace poly
