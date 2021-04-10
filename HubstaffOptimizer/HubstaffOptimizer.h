#pragma once

#include <vector>

#include "IHubstaffOptimizer.h"

class HubstaffOptimizer : public IHubstaffOptimizer
{
public:
    explicit HubstaffOptimizer(IHubstaffOptimizer::StockData theStockData, int theFee);
    ~HubstaffOptimizer() = default;

    int GetMaximumProfit() const override;

private:
    StockData stockData;
    int fee = 0;

    bool StockPriceIsLowest(int dayIndex, int currentLowestPriceDay) const;
    int CalculateProfit(int lowestIndex, int highestIndex) const;
};
