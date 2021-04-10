#include "HubstaffOptimizer.h"

#include <iostream>
#include <vector>

HubstaffOptimizer::HubstaffOptimizer(IHubstaffOptimizer::StockData theStockData, int theFee)
    :
    IHubstaffOptimizer(),
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
    // Calculate profit of given stock exchange and fee.

    const auto currentLowestPrice = stockData[lowestIndex];
    const auto highestPrice = stockData[highestIndex];
    const int profit = highestPrice - fee - currentLowestPrice - fee;

    return profit;
}
 
int HubstaffOptimizer::GetMaximumProfit() const
{
    /*
        Calculate max profit using iterational implementation of optimizer.
        May handle multiple exchanges.
        Returns the total sum of all optimal exchanges (highest-lower incl. fee).
    */

    int currentLowestPriceDayIndex = -1;
    int profitSum = 0;
    int currentMaxProfit = 0;
    int currentMaxProfitIndex = 0;

    for (int dayNumber = 0;;)
    {
        if (dayNumber >= stockData.size())
        {
            // we reach end of data
            if (currentMaxProfit <= 0)
            {
                // no more profits found
                break;
            }

            // add current max profit to the sum of total profits found
            profitSum += currentMaxProfit;

            // restart loop to the place where highest stock data sample was found
            // but we also need to skip one day (resting)
            dayNumber = currentMaxProfitIndex + 2;
            currentLowestPriceDayIndex = -1;
            currentMaxProfit = 0;
            continue;
        }

        const int stockPrice = stockData[dayNumber];

        if (currentLowestPriceDayIndex < 0 ||
            StockPriceIsLowest(dayNumber, currentLowestPriceDayIndex))
        {
            // end of "local max" - take that into consideration
            if (currentMaxProfit > 0)
            {
                profitSum += currentMaxProfit;
                currentMaxProfit = 0;
                // cool down one extra day
                dayNumber += 1;
                currentLowestPriceDayIndex = -1;
                continue;
            }

            currentLowestPriceDayIndex = dayNumber;
            ++dayNumber;
            continue;
        }

        const auto profit = CalculateProfit(currentLowestPriceDayIndex, dayNumber);

        if (profit > currentMaxProfit)
        {
            currentMaxProfit = profit;
            currentMaxProfitIndex = dayNumber;
        }

        ++dayNumber;
    }

    return profitSum;
}
