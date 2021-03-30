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

    HubstaffOptimizer optimizer;
}
