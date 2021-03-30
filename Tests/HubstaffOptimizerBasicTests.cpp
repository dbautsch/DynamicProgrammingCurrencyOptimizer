#include <gtest/gtest.h>

#include "HubstaffOptimizer.h"

TEST(HubstaffOptimizerBasicTests, CanInitializeClass)
{
    /*
        Lets try to initialize an empty object of optimizer class.
        On some platforms there are different mechanisms of dynamic
        linking involved and this is what this case is testing - if
        the class simply is being correctly exported.
    */

    HubstaffOptimizer optimizer({}, 0);
}

TEST(HubstaffOptimizerBasicTests, CanWorkWithEmptyArray)
{
    HubstaffOptimizer optimizer({}, 0);

    int result = 0;
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 0);
}

TEST(HubstaffOptimizerBasicTests, CanSolveSimpleCase)
{
    HubstaffOptimizer::StockData stockData{1, 2, 1, 10, 15, 2};
    const int fee = 1;

    int result = 0;
    HubstaffOptimizer optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 7);
}
