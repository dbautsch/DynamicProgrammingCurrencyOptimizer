#pragma once

#include <vector>

#include "IOptimizer.h"

class OptimizerDynamic : public IOptimizer
{
public:
    explicit OptimizerDynamic(IOptimizer::StockData theStockData, int theFee);
    ~OptimizerDynamic() = default;

    int GetMaximumProfit() const override;

private:
    using ProfitsContainer = std::vector<int>;
    using TransactionsContainer = std::vector<ProfitsContainer>;

    IOptimizer::StockData stockData;
    int fee = 0;

    int CalculateProfit(int leftProfit, int rightProfit, int fee) const;
};
