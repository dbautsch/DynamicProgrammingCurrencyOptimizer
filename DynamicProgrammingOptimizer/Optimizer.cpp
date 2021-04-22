/*
MIT License

Copyright (c) 2021 Dawid Bautsch

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Optimizer.h"

#include <iostream>
#include <vector>

Optimizer::Optimizer(IOptimizer::StockData theStockData, int theFee)
    :
    IOptimizer(),
    stockData(std::move(theStockData)), fee(theFee)
{
    
}

bool Optimizer::StockPriceIsLowest(int dayIndex,
    int currentLowestPriceDay) const
{
    const auto currentLowestPrice = stockData[currentLowestPriceDay];
    const auto testedPrice = stockData[dayIndex];

    return testedPrice < currentLowestPrice;
}

int Optimizer::CalculateProfit(int lowestIndex, int highestIndex) const
{
    // Calculate profit of given stock exchange and fee.

    const auto currentLowestPrice = stockData[lowestIndex];
    const auto highestPrice = stockData[highestIndex];
    const int profit = highestPrice - fee - currentLowestPrice - fee;

    return profit;
}
 
int Optimizer::GetMaximumProfit() const
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
