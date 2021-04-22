cmake_minimum_required(VERSION 3.10)

# set the project name
project(DynamicProgrammingOptimizerChallenge)

file(GLOB DynamicProgrammingOptimizer_SRC
    "DynamicProgrammingOptimizer/*.cpp"
    "DynamicProgrammingOptimizer/*.h"
)

file(GLOB Tests_SRC
    "Tests/*.cpp"
    "Tests/*.h"
)

# DynamicProgrammingOptimizer shared library
add_library(DynamicProgrammingOptimizer SHARED ${DynamicProgrammingOptimizer_SRC})
set_property(TARGET DynamicProgrammingOptimizer PROPERTY CXX_STANDARD 17)

# DynamicProgrammingOptimizer tests
add_executable(tests ${Tests_SRC})
set_property(TARGET tests PROPERTY CXX_STANDARD 17)
target_link_libraries(tests gtest)
if (UNIX)
target_link_libraries(tests pthread)
endif (UNIX)
target_link_libraries(tests DynamicProgrammingOptimizer)
target_include_directories(tests PRIVATE DynamicProgrammingOptimizer)
