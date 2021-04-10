#pragma once

#include <vector>

#include "IHubstaffOptimizer.h"

class HubstaffOptimizerDynamic : public IHubstaffOptimizer
{
public:
    explicit HubstaffOptimizerDynamic(IHubstaffOptimizer::StockData theStockData, int theFee);
    ~HubstaffOptimizerDynamic() = default;

    int GetMaximumProfit() const override;

private:
    using ProfitsContainer = std::vector<int>;
    using TransactionsContainer = std::vector<ProfitsContainer>;

    IHubstaffOptimizer::StockData stockData;
    int fee = 0;

    int CalculateProfit(int leftProfit, int rightProfit, int fee) const;
};
