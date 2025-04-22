#pragma once
#include "poly.hpp"
#include <cmath>
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

template <poly::Arithmetic T>
struct std::formatter<poly::Poly<T>, char>
{
    template <class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();

        // std::from_chars(it, ctx.end(), n);

        while (it != ctx.end() && *it != '}') {
            it++;
        }

        return it;
    }

    template <typename FmtContext>
    FmtContext::iterator format(const poly::Poly<T>& obj, FmtContext& ctx) const
    {
        auto out = ctx.out();
        bool first = true;
        if (obj.getDegree() == -1) {
            return std::format_to(out, "0");
        }
        if (obj.getDegree() == 0) {
            const T& coef = obj[0];
            std::format_to(out, "{}", (coef > T{} ? "+" : "-"));
            std::format_to(out, "{}", coef);
            return out;
        }
        for (int i = 0; i <= obj.getDegree(); i++) {
            const T& coef = obj[i];

            if (coef == 0) {
                continue;
            }

            if (!first) {
                std::format_to(out, " {} ", (coef > T{} ? "+" : "-"));
            } else if (coef < 0) {
                std::format_to(out, "-");
            }

            if (std::abs(coef) != 1 || i == 0) {
                std::format_to(out, "{}", std::abs(coef));
            }
            if (i > 0) {
                std::format_to(out, "x");
            }
            if (i > 1) {
                std::format_to(out, "^{}", i);
            }

            first = false;
        }
        return out;
    }
};
