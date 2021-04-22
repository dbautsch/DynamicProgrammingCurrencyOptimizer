#include <gtest/gtest.h>

#include "OptimizerDynamic.h"
#include "IOptimizer.h"

TEST(OptimizerDynamicBasicTests, CanInitializeClass)
{
    /*
        Lets try to initialize an empty object of optimizer class.
        On some platforms there are different mechanisms of dynamic
        linking involved and this is what this case is testing - if
        the class simply is being correctly exported.
    */

    OptimizerDynamic optimizer({}, 0);
}

TEST(OptimizerDynamicBasicTests, CanWorkWithEmptyArray)
{
    OptimizerDynamic optimizer({}, 0);

    int result = 0;
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 0);
}

TEST(OptimizerDynamicBasicTests, CanSolveSimpleCase)
{
    IOptimizer::StockData stockData{1, 2, 1, 10, 15, 2};
    const int fee = 1;

    int result = 0;
    OptimizerDynamic optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 13);
}

TEST(OptimizerDynamicBasicTests, CanSolveMultipleExchanges)
{
    IOptimizer::StockData stockData{1, 2, 1, 10, 15, 2, 7, 13};
    const int fee = 1;

    int result = 0;
    OptimizerDynamic optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 17);
}

TEST(OptimizerDynamicBasicTests, CanSolveSingleElementArray)
{
    IOptimizer::StockData stockData{1};
    const int fee = 1;

    int result = 0;
    OptimizerDynamic optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 0 );
}

TEST(OptimizerDynamicBasicTests, CanSolveSpecialCase)
{
    /*
        special case 2 (101)
        2,  3,  50, 1,  90, 80, 1,  17
                    |    |      |   |
                    ------      -----
                       |          |
                       87         14
    */

    IOptimizer::StockData stockData{2, 3, 50, 1, 90, 80, 1, 17};
    const int fee = 1;

    int result = 0;
    OptimizerDynamic optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 101 );
}
