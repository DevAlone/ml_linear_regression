#pragma once

#include "gradient_descent.h"

#include <cassert>
#include <cmath>
#include <functional>
#include <utility>
#include <vector>

namespace ml {

template <typename ArgumentType>
ArgumentType getFitsCoefficient(
    const std::vector<std::pair<ArgumentType, ArgumentType> >& points,
    const ArgumentType theta0,
    const ArgumentType theta1)
{
    ArgumentType result = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        const auto x = points[i].first;
        const auto y = points[i].second;

        result += std::pow(theta0 + theta1 * x - y, 2);
        //        result += theta0 + theta1 * x - y;
    }

    // return result / (2 * (points.size() + 1));
    return result / (points.size() + 1);
}

template <typename ArgumentType>
ArgumentType getFitsCoefficientWrapper(
    const ArgumentType theta0,
    const ArgumentType theta1)
{
}

template <typename ArgumentType>
std::pair<ArgumentType, ArgumentType> getLineFitsToPoints(
    const std::vector<std::pair<ArgumentType, ArgumentType> >& points)
{
    GradientDescent<ArgumentType> gradientDescent;
    bool runOutOfMaximumSteps;

    auto result = gradientDescent.calculate(
        [points](const ArgumentType theta0, const ArgumentType theta1) {
            return getFitsCoefficient(points, theta0, theta1);
        },
        0,
        0, &runOutOfMaximumSteps);

    assert(!runOutOfMaximumSteps);

    return result;
}
}
