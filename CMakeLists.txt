cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra --pedantic -Werror -fconcepts")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment -Wno-unused-function")

project(Flex-And-Bison)

add_subdirectory(${PROJECT_SOURCE_DIR}/book/chapter-1)
add_subdirectory(${PROJECT_SOURCE_DIR}/book/chapter-2)
add_subdirectory(${PROJECT_SOURCE_DIR}/own/phptools)


file(GLOB_RECURSE SRC_FILES
        "lib/*.h"
        "lib/*.cpp"
        "lib/*.hpp"
        )
add_library(common ${SRC_FILES})
target_include_directories(common PUBLIC lib/symbol_table)

# testing

find_package (Boost COMPONENTS unit_test_framework REQUIRED)
file(GLOB_RECURSE unit_test_sources tests/*.cpp)
add_executable(unit_test ${unit_test_sources})
target_link_libraries(unit_test PUBLIC common)
enable_testing()
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
ADD_TEST (Test unit_test)