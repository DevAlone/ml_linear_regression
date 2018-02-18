#pragma once

#include <cmath>
#include <functional>
#include <iostream>

namespace ml {

template <typename Function, typename ArgumentType = double>
std::pair<ArgumentType, ArgumentType> getGradient(
    const Function function, const ArgumentType x, const ArgumentType y, const ArgumentType delta)
{
    const ArgumentType xDelta = function(x + delta, y) - function(x - delta, y);
    const ArgumentType yDelta = function(x, y + delta) - function(x, y - delta);

    return std::make_pair(
        xDelta / (2 * delta),
        yDelta / (2 * delta));
}

template <typename ArgumentType>
class GradientDescent {
public:
    GradientDescent(
        const ArgumentType learningRate = 0.1,
        size_t maximumStepsCount = 1048576u,
        const ArgumentType precision = 0.0001)

        : learningRate(learningRate)
        , precision(precision)
        , maximumStepsCount(maximumStepsCount)
    {
    }

    template <typename Function>
    std::pair<ArgumentType, ArgumentType> calculate(
        const Function function,
        const ArgumentType initX,
        const ArgumentType initY,
        bool* const runOutOfMaximumSteps = nullptr)
    {
        ArgumentType bestX = initX;
        ArgumentType bestY = initY;

        ArgumentType xDelta, yDelta;
        xDelta = yDelta = precision * 2;

        auto i = maximumStepsCount;
        while (i && (xDelta > precision || yDelta > precision)) {
            ArgumentType newX, newY;

            auto pair = getGradient(function, bestX, bestY, learningRate);

            newX = bestX - learningRate * pair.first;
            newY = bestY - learningRate * pair.second;

            xDelta = std::abs(newX - bestX);
            yDelta = std::abs(newY - bestY);

            bestX = newX;
            bestY = newY;
            --i;
        }

        if (runOutOfMaximumSteps)
            *runOutOfMaximumSteps = i == 0;

        return std::make_pair(bestX, bestY);
    }

private:
    const ArgumentType learningRate;
    const ArgumentType precision;
    const size_t maximumStepsCount;
};
}
