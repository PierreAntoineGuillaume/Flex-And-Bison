cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

find_package(FLEX)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

macro (flex_executable name file)
    FLEX_TARGET(scanner_${name} ${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_BINARY_DIR}/${name}.ll.cpp)
    add_executable(${name} ${FLEX_scanner_${name}_OUTPUTS})
endmacro(flex_executable)

flex_executable(wc wc.l)
flex_executable(fb2-2 wc.l)
