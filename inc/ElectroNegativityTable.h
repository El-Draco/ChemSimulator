#pragma once
#include "ErrorHandler.h"
#include "Atom.h"
#include <concepts>

class ElectroNegativity
{
public:
    static const constexpr double data[118]{
        2.2,
        ERROR::NO_DATA,
        0.98,
        1.57,
        2.04,
        2.55,
        3.04,
        3.44,
        3.98,
        ERROR::NO_DATA,
        0.93,
        1.31,
        1.61,
        1.90,
        2.19,
        2.58,
        3.16,
        ERROR::NO_DATA,
        0.82,
        1.00,
        1.36,
        1.54,
        1.63,
        1.66,
        1.55,
        1.83,
        1.88,
        1.91,
        1.90,
        1.65,
        1.81,
        2.01,
        2.18,
        2.55,
        2.96,
        3,
        0.82,
        0.95,
        1.22,
        1.33,
        1.6,
        2.16,
        1.9,
        2.2,
        2.28,
        2.2,
        1.93,
        1.69,
        1.78,
        1.96,
        2.05,
        2.1,
        2.66,
        2.6,
        0.79,
        0.89,
        1.1,
        1.12,
        1.13,
        1.14,
        1.13,
        1.17,
        1.2,
        1.2,
        1.22,
        1.23,
        1.24,
        1.24,
        1.25,
        1.1,
        1.27,
        1.3,
        1.5,
        2.36,
        1.9,
        2.2,
        2.2,
        2.28,
        2.54,
        2,
        1.62,
        2.33,
        2.02,
        2,
        2.2,
        ERROR::NO_DATA,
        0.7,
        0.89,
        1.1,
        1.3,
        1.5,
        1.38,
        1.36,
        1.28,
        1.3,
        1.3,
        1.3,
        1.3,
        1.3,
        1.3,
        1.3,
        1.3,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
        ERROR::NO_DATA,
    };

public:
    template <typename T = Atom>
    // requires std::same_as<T, int> ||
    //          std::same_as<T, Atom>
    static const float ID(const T &input)
    {
        if (std::is_same<T, Atom>())
        {
            return static_cast<float>(data[input.protons - 1]);
        }
        // if (std::is_same<T, int>())
        // {
        //     return static_cast<float>(data[input - 1]);
        // }
        return (-9.99f);
    }
};
