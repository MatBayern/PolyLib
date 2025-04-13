#pragma once
#include <cmath>
#include <concepts>
#include <print>
#include <stdexcept>
#include <utility>
#include <vector>
namespace poly {

/**
 *  @short his concept ensures that the necessary arithmetic operations are defined.
 */
template <typename T>
concept Arithmetic = requires(T a, T b) {
    { a + b }
        -> std::convertible_to<T>;
    { a - b }
        -> std::convertible_to<T>;
    { a * b }
        -> std::convertible_to<T>;
    { a / b }
        -> std::convertible_to<T>;
    { -a }
        -> std::convertible_to<T>;
    { a == b } -> std::convertible_to<bool>;
};

template <Arithmetic T>
class poly
{

private:
    size_t _degree = 0;
    std::vector<T> _coeff;

public:
    poly(size_t degree) : _degree(degree), _coeff(degree + 1) {};
    poly(std::initializer_list<T> l) : _degree(l.size() - 1), _coeff(l) {};
    ~poly() = default;
    poly() = default;
    /**
     *
     *  Operator Overloading
     *
     */
    T& operator[](const size_t& index)
    {
        if (index >= _degree + 1) {
            throw std::runtime_error("invalid access");
        }
        return _coeff[index];
    }

    T operator[](const size_t& index) const
    {
        if (index >= _degree + 1) {
            throw std::runtime_error("invalid access");
        }
        return _coeff[index];
    }

    T operator()(const T& x) const
    {
        T result = _coeff[_degree];
        for (int i = _degree - 1; i >= 0; i--) {
            result = result * x + _coeff[i]; // using Horner schema
        }
        return result;
    }

    poly<T> operator+(const poly<T>& other) const
    {
        poly<T> result(std::max(_degree, other._degree)); // slect the maximum degree of the resulting polynomial
        for (size_t i = 0; i <= std::max(_degree, other._degree); i++) {
            result[i] = (i <= _degree ? _coeff[i] : T{}) + (i <= other._degree ? other._coeff[i] : T{});
        }
        return result;
    }

    poly<T> operator-(const poly<T>& other) const
    {
        return *this + (-other);
    }

    poly<T> operator*(const poly<T>& other) const
    {
        poly<T> result(_degree + other._degree);
        for (size_t i = 0; i <= _degree; i++) {
            for (size_t j = 0; j <= other.getDegree(); j++) {
                T tmp = _coeff[i] * other[j];
                result[i + j] = result[i + j] + tmp;
            }
        }
        return result;
    }
    /**
     *
     * Operator for Scalar Multiplaktion
     */
    poly<T> operator*(const T& other) const
    {
        poly<T> result(*this);
        for (size_t i = 0; i <= _degree; i++) {
            result[i] = result[i] * other;
        }
        return result;
    }

    poly<T> operator/(const T& other) const
    {
        poly<T> result(*this);
        for (size_t i = 0; i <= _degree; i++) {

            result[i] = result[i] / other;
        }
        return result;
    }

    poly<T> operator-() const
    {
        poly<T> result(_degree);
        for (size_t i = 0; i <= _degree; i++) {
            result[i] = -_coeff[i];
        }
        return result;
    }

    template <Arithmetic U>
    bool operator==(const poly<U>& /**/) const
    {
        return false;
    }

    bool operator==(const poly<T>& other) const
    {
        if (_degree != other.getDegree()) {
            return false;
        }
        for (size_t i = 0; i <= _degree; i++) {
            if (_coeff[i] != other[i]) {
                return false;
            }
        }
        return true;
    }
    /**
     *
     *  Getters and setters
     *
     */
    /**
     *
     * @short This will return the degree of the polynom
     */
    size_t getDegree() const noexcept
    {
        return _degree;
    }

    /**
     *
     *
     *  derivative
     *
     */
    /**
     * @short this will take the derivative of this polynomial
     *
     */
    void derivative() noexcept
    {
        if (_degree == 0) {
            return;
        }

        std::vector<T> tmp;
        tmp.resize(_degree);
        for (size_t i = 1; i <= _degree; i++) {
            tmp[i - 1] = _coeff[i] * i;
        }
        _coeff = std::move(tmp);
        --_degree;
    }
    /**
     * @short this will integrate the polynom and return the Value
     * @param[in] a lower bound
     * @param[in] b upper bound
     *
     */
    T intregrate(const T& a, const T& b) const
    {
        if (a == b)
        {
            return T{}; // return 0 if upper and lower bound are the same
        }
        
        poly p(_degree + 1);
        for (size_t i = 1; i <= _degree + 1; i++) {
            if (_coeff[i - 1] == T{}) {
                p[i] = T{};
                continue;
            }
            p[i] = _coeff[i - 1] / static_cast<T>(i);
        }
        return p(b) - p(a);
    }
};
} // namespace poly
