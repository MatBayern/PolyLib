#pragma once
#include <cmath>
#include <concepts>
#include <iterator>
#include <print>
#include <stdexcept>
#include <utility>
#include <vector>
namespace poly {

/**
 *  @short This concept ensures that the necessary arithmetic operations are defined.
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
class Poly
{

private:
    size_t _degree = 0;
    std::vector<T> _coefficent;

public:
    explicit Poly(size_t degree) : _degree(degree), _coefficent(degree + 1) {};
    Poly(std::initializer_list<T> l) : _degree(l.size() - 1), _coefficent(l) {};
    explicit Poly(const std::vector<T>& vec) : _degree(vec.size() - 1), _coefficent(vec) {};
    explicit Poly(std::vector<T>&& vec) : _degree(vec.size() - 1), _coefficent(std::move(vec)) {};

    template <std::forward_iterator Iterator>
    Poly(Iterator begin, Iterator end) : _degree(std::distance(begin, end) - 1), _coefficent(std::distance(begin, end))
    {
        std::size_t n = 0;
        for (auto it = begin; it != end; ++it) {
            _coefficent[n] = *it;
            n++;
        }
    };

    ~Poly() = default;
    Poly() = default;
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
        return _coefficent[index];
    }

    T operator[](const size_t& index) const
    {
        if (index >= _degree + 1) {
            throw std::runtime_error("invalid access");
        }
        return _coefficent[index];
    }

    T operator()(const T& x) const
    {
        T result = _coefficent[_degree];
        for (int i = _degree - 1; i >= 0; i--) {
            result = result * x + _coefficent[i]; // using Horner schema
        }
        return result;
    }

    Poly<T> operator+(const Poly<T>& other) const
    {
        Poly<T> result(std::max(_degree, other._degree)); // slect the maximum degree of the resulting polynomial
        for (size_t i = 0; i <= std::max(_degree, other._degree); i++) {
            result[i] = (i <= _degree ? _coefficent[i] : T{}) + (i <= other._degree ? other._coefficent[i] : T{});
        }
        return result;
    }

    Poly<T> operator-(const Poly<T>& other) const
    {
        Poly<T> tmp = *this + (-other);
        const int N = tmp.getDegree();
        for (int i = N; i >= 0; i--) {
            if (tmp[i] != T{}) {
                return tmp;
            }
            tmp._degree--;
        }

        return Poly<T>{};
    }

    Poly<T> operator*(const Poly<T>& other) const
    {
        Poly<T> result(_degree + other._degree);
        for (size_t i = 0; i <= _degree; i++) {
            for (size_t j = 0; j <= other.getDegree(); j++) {
                T tmp = _coefficent[i] * other[j];
                result[i + j] = result[i + j] + tmp;
            }
        }
        return result;
    }
    /**
     *
     * @short Operator for Scalar Multiplaktion
     */
    Poly<T> operator*(const T& other) const
    {
        Poly<T> result(*this);
        for (size_t i = 0; i <= _degree; i++) {
            result[i] = result[i] * other;
        }
        return result;
    }

    Poly<T> operator/(const T& other) const
    {
        Poly<T> result(*this);
        for (size_t i = 0; i <= _degree; i++) {

            result[i] = result[i] / other;
        }
        return result;
    }

    Poly<T> operator-() const
    {
        Poly<T> result(_degree);
        for (size_t i = 0; i <= _degree; i++) {
            result[i] = -_coefficent[i];
        }
        return result;
    }

    template <Arithmetic U>
    bool operator==(const Poly<U>& /**/) const noexcept
    {
        return false;
    }

    bool operator==(const Poly<T>& other) const
    {
        if (_degree != other.getDegree()) {
            return false;
        }
        for (size_t i = 0; i <= _degree; i++) {
            if (_coefficent[i] != other[i]) {
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
    void derivative()
    {
        if (_degree == 0) {
            return;
        }

        std::vector<T> tmp;
        tmp.resize(_degree);
        for (size_t i = 1; i <= _degree; i++) {
            tmp[i - 1] = _coefficent[i] * i;
        }
        _coefficent = std::move(tmp);
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
        if (a == b) {
            return T{}; // return 0 if upper and lower bound are the same
        }

        Poly p(_degree + 1);
        for (size_t i = 1; i <= _degree + 1; i++) {
            if (_coefficent[i - 1] == T{}) {
                p[i] = T{};
                continue;
            }
            p[i] = _coefficent[i - 1] / static_cast<T>(i);
        }
        return p(b) - p(a);
    }
};
} // namespace poly
