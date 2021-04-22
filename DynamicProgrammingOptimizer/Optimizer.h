#pragma once

#include <vector>

#include "IOptimizer.h"

class Optimizer : public IOptimizer
{
public:
    explicit Optimizer(IOptimizer::StockData theStockData, int theFee);
    ~Optimizer() = default;

    int GetMaximumProfit() const override;

private:
    StockData stockData;
    int fee = 0;

    bool StockPriceIsLowest(int dayIndex, int currentLowestPriceDay) const;
    int CalculateProfit(int lowestIndex, int highestIndex) const;
};
