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
