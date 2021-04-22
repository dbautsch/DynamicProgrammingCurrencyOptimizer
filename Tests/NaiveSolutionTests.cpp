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
