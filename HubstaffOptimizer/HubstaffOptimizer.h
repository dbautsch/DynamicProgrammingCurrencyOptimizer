#pragma once

#include <vector>

class HubstaffOptimizer
{
public:
    using StockData = std::vector<int>;

    explicit HubstaffOptimizer(StockData theStockData, int theFee);
    ~HubstaffOptimizer() = default;

    int GetMaximumProfit() const;

private:
    StockData stockData;
    int fee = 0;
};
