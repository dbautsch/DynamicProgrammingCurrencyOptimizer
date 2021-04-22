#pragma once

#include <vector>

class IOptimizer
{
public:
    using StockData = std::vector<int>;

    IOptimizer() = default;
    ~IOptimizer() = default;

    virtual int GetMaximumProfit() const = 0;
};
