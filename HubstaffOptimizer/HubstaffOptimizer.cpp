#include "HubstaffOptimizer.h"

#include <iostream>

HubstaffOptimizer::HubstaffOptimizer(StockData theStockData, int theFee)
    :
    stockData(std::move(theStockData)), fee(theFee)
{
    
}

bool HubstaffOptimizer::StockPriceIsLowest(int dayIndex,
    int currentLowestPriceDay) const
{
    const auto currentLowestPrice = stockData[currentLowestPriceDay];
    const auto testedPrice = stockData[dayIndex];

    return testedPrice < currentLowestPrice;
}

int HubstaffOptimizer::CalculateProfit(int lowestIndex, int highestIndex) const
{
    const auto currentLowestPrice = stockData[lowestIndex];
    const auto highestPrice = stockData[highestIndex];
    const int profit = highestPrice - fee - currentLowestPrice - fee;

    return profit;
}
 
int HubstaffOptimizer::GetMaximumProfit() const
{
    int currentLowestPriceDayIndex = -1;
    int profitSum = 0;
    int currentMaxProfit = 0;
    int currentMaxProfitIndex = 0;

    for (int dayNumber = 0;;)
    {
        if (dayNumber + 1 >= stockData.size())
        {
            if (currentMaxProfit <= 0)
            {
                // no profits found
                break;
            }

            profitSum += currentMaxProfit;

            // restart loop to the place where highest stock data sample was found + 1 day
            dayNumber = currentMaxProfitIndex + 1;
            currentLowestPriceDayIndex = -1;
            currentMaxProfit = 0;
            continue;
        }

        const int stockPrice = stockData[dayNumber];

        if (currentLowestPriceDayIndex < 0 ||
            StockPriceIsLowest(dayNumber, currentLowestPriceDayIndex))
        {
            // take that into consideration
            currentLowestPriceDayIndex = dayNumber;
            ++dayNumber;
            continue;
        }

        ++dayNumber;
        const auto profit = CalculateProfit(currentLowestPriceDayIndex, dayNumber);

        if (profit > currentMaxProfit)
        {
            currentMaxProfit = profit;
            currentMaxProfitIndex = dayNumber;
        }
    }

    return profitSum;
}
