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

#include "OptimizerDynamic.h"

#include <limits>
#include <array>
#include <deque>

OptimizerDynamic:OptimizerDynamic(
    IOptimizer::StockData theStockData, int theFee)
    :
    IOptimizer(),
    stockData(std::move(theStockData)), fee(theFee)
{

}

int OptimizerDynamic::CalculateProfit(
    int leftProfit,
    int rightProfit,
    int fee) const
{
    return leftProfit - rightProfit - (fee * 2);
}

int OptimizerDynamic::GetMaximumProfit() const
{
    if (stockData.size() < 2)
    {
        return 0;
    }

    std::deque<int> profitsBuffer;
    int highestProfitSum = 0;

    int currentMaxProfit = std::max(-(stockData[0] + fee), -(stockData[1] + fee));

    profitsBuffer.push_back(0);
    profitsBuffer.push_back(std::max(*profitsBuffer.begin(), currentMaxProfit + stockData[1] - fee));

    for (int dayNumber = 2; dayNumber < stockData.size(); ++dayNumber)
    {
        const auto newProfit = 
            CalculateProfit(*profitsBuffer.begin(), stockData[dayNumber], fee);

        currentMaxProfit = std::max(currentMaxProfit, newProfit);
        const auto currentProfit = 
            std::max(*(profitsBuffer.begin()++), currentMaxProfit + stockData[dayNumber]);

        profitsBuffer.push_back(currentProfit);
        highestProfitSum = std::max(highestProfitSum, currentProfit);

        profitsBuffer.pop_front();
    }
    
    return highestProfitSum;
}
