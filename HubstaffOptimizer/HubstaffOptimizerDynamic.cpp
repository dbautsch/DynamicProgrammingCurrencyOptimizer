#include "HubstaffOptimizerDynamic.h"

#include <limits>
#include <array>
#include <deque>

HubstaffOptimizerDynamic::HubstaffOptimizerDynamic(
    IHubstaffOptimizer::StockData theStockData, int theFee)
    :
    IHubstaffOptimizer(),
    stockData(std::move(theStockData)), fee(theFee)
{

}

int HubstaffOptimizerDynamic::CalculateProfit(
    int leftProfit,
    int rightProfit,
    int fee) const
{
    return leftProfit - rightProfit - (fee * 2);
}

int HubstaffOptimizerDynamic::GetMaximumProfit() const
{
    if (stockData.size() < 2)
    {
        return 0;
    }

    //  TODO - use circular buffer or queue to reduce memory complexity
    
    /*
    std::vector<int> profitsCache(stockData.size());

    int highestProfitSum = 0;

    profitsCache[0] = 0;
    profitsCache[1] = std::max(profitsCache[0], currentMaxProfit + stockData[1] - fee);

    for (int dayNumber = 2; dayNumber < stockData.size(); ++dayNumber)
    {
        const auto newProfit = 
            CalculateProfit(profitsCache[dayNumber - 2], stockData[dayNumber], fee);

        currentMaxProfit = std::max(currentMaxProfit, newProfit);
        const auto currentProfit = 
            std::max(profitsCache[dayNumber - 1], currentMaxProfit + stockData[dayNumber]);

        profitsCache[dayNumber] = currentProfit;
        highestProfitSum = std::max(highestProfitSum, currentProfit);
    }
    */

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