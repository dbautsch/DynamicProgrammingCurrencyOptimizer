#pragma once

#include <vector>

class IHubstaffOptimizer
{
public:
    using StockData = std::vector<int>;

    IHubstaffOptimizer() = default;
    ~IHubstaffOptimizer() = default;

    virtual int GetMaximumProfit() const = 0;
};
