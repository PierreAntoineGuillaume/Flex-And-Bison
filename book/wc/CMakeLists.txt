cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

find_package(FLEX)


FLEX_TARGET(scanner ${CMAKE_CURRENT_SOURCE_DIR}/wc.l ${CMAKE_CURRENT_BINARY_DIR}/wc.ll.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(wc ${FLEX_scanner_OUTPUTS})