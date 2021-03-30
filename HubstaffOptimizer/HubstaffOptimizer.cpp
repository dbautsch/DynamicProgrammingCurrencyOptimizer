#include "HubstaffOptimizer.h"

#include <iostream>

HubstaffOptimizer::HubstaffOptimizer(StockData theStockData, int theFee)
    :
    stockData(std::move(theStockData)), fee(theFee)
{
    
}

int HubstaffOptimizer::GetMaximumProfit() const
{
    return 0;
}
