#include <gtest/gtest.h>

#include "Optimizer.h"

TEST(OptimizerBasicTests, CanInitializeClass)
{
    /*
        Lets try to initialize an empty object of optimizer class.
        On some platforms there are different mechanisms of dynamic
        linking involved and this is what this case is testing - if
        the class simply is being correctly exported.
    */

    Optimizer optimizer({}, 0);
}

TEST(OptimizerBasicTests, CanWorkWithEmptyArray)
{
    Optimizer optimizer({}, 0);

    int result = 0;
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 0);
}

TEST(OptimizerBasicTests, CanSolveSimpleCase)
{
    IOptimizer::StockData stockData{1, 2, 1, 10, 15, 2};
    const int fee = 1;

    int result = 0;
    Optimizer optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 12);
}

TEST(OptimizerBasicTests, CanSolveMultipleExchanges)
{
    IOptimizer::StockData stockData{1, 2, 1, 10, 15, 2, 7, 13};
    const int fee = 1;

    int result = 0;
    Optimizer optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 16 );
}

TEST(OptimizerBasicTests, CanSolveSingleElementArray)
{
    IOptimizer::StockData stockData{1};
    const int fee = 1;

    int result = 0;
    Optimizer optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 0 );
}

TEST(OptimizerBasicTests, CanSolveSpecialCase)
{
    /*
    special case (profit sum = 60)
        2,  3,  50, 1,  90, 80, 1,  17
        |        |              |    |
        ----------              ------
            |                      |
            46                    14
    */

    IOptimizer::StockData stockData{2, 3, 50, 1, 90, 80, 1, 17};
    const int fee = 1;

    int result = 0;
    Optimizer optimizer(stockData, fee);
    EXPECT_NO_THROW(result = optimizer.GetMaximumProfit());
    EXPECT_EQ(result, 60 );
}

/*
    special case (60)
        2,  3,  50, 1,  90, 80, 1,  17
        |        |              |    |
        ----------              ------
            |                      |
            46                    14


    special case 2 (101)
        2,  3,  50, 1,  90, 80, 1,  17
                    |    |      |   |
                    ------      -----
                       |          |
                       87         14
*/
