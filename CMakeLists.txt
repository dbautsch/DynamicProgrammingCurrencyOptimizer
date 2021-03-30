cmake_minimum_required(VERSION 3.10)

# set the project name
project(HubstaffChallenge)

file(GLOB HubstaffOptimizer_SRC
    "HubstaffOptimizer/*.cpp"
    "HubstaffOptimizer/*.h"
)

file(GLOB Tests_SRC
    "Tests/*.cpp"
    "Tests/*.h"
)

# HubstaffOptimizer shared library
add_library(hubstaffOptimizer SHARED ${HubstaffOptimizer_SRC})
set_property(TARGET hubstaffOptimizer PROPERTY CXX_STANDARD 17)

# HubstaffOptimizer tests
add_executable(tests ${Tests_SRC})
set_property(TARGET tests PROPERTY CXX_STANDARD 17)
target_link_libraries(tests gtest)
if (UNIX)
target_link_libraries(tests pthread)
endif (UNIX)
target_link_libraries(tests hubstaffOptimizer)
target_include_directories(tests PRIVATE HubstaffOptimizer)
