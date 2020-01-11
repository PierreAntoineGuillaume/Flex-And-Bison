project(TrimNonPhp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -pedantic")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})

find_package(FLEX)

add_definitions(-DYY_NO_UNPUT)

set(CMAKE_CXX_STANDARD 17)

flex_executable(cleanPhp trimphp.l)
