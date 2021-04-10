#include <gtest/gtest.h>

#include "HubstaffOptimizerDynamic.h"
#include "IHubstaffOptimizer.h"

TEST(HubstaffOptimizerDynamicBasicTests, CanInitializeClass)
{
    /*
        Lets try to initialize an empty object of optimizer class.
        On some platforms there are different mechanisms of dynamic
        linking involved and this is what this case is testing - if
        the class simply is being correctly exported.
    */

    HubstaffOptimizerDynamic optimizer({}, 0);
}

TEST(HubstaffOptimizerDynamicBasicTests, CanWorkWithEmptyArray)
{
    HubstaffOptimizerDynamic optimizer({}, 0);

    int result = 0;
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 0);
}

TEST(HubstaffOptimizerDynamicBasicTests, CanSolveSimpleCase)
{
    IHubstaffOptimizer::StockData stockData{1, 2, 1, 10, 15, 2};
    const int fee = 1;

    int result = 0;
    HubstaffOptimizerDynamic optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 13);
}

TEST(HubstaffOptimizerDynamicBasicTests, CanSolveMultipleExchanges)
{
    IHubstaffOptimizer::StockData stockData{1, 2, 1, 10, 15, 2, 7, 13};
    const int fee = 1;

    int result = 0;
    HubstaffOptimizerDynamic optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 17);
}

TEST(HubstaffOptimizerDynamicBasicTests, CanSolveSingleElementArray)
{
    IHubstaffOptimizer::StockData stockData{1};
    const int fee = 1;

    int result = 0;
    HubstaffOptimizerDynamic optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 0 );
}

TEST(HubstaffOptimizerDynamicBasicTests, CanSolveSpecialCase)
{
    /*
        special case 2 (101)
        2,  3,  50, 1,  90, 80, 1,  17
                    |    |      |   |
                    ------      -----
                       |          |
                       87         14
    */

    IHubstaffOptimizer::StockData stockData{2, 3, 50, 1, 90, 80, 1, 17};
    const int fee = 1;

    int result = 0;
    HubstaffOptimizerDynamic optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 101 );
}
