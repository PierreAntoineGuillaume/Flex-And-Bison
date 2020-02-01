cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra --pedantic -Werror -fconcepts")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment -Wno-unused-function")

project(Flex-And-Bison)
find_package(BISON)
find_package(FLEX)

file(GLOB_RECURSE SRC_FILES
        "lib/*.h"
        "lib/*.cpp"
        "lib/*.hpp")

set(LEXING          ${PROJECT_SOURCE_DIR}/lib/lexing)
set(SYMBOL_TABLE    ${PROJECT_SOURCE_DIR}/lib/symbol_table)
set(AST             ${PROJECT_SOURCE_DIR}/lib/ast)

find_package(FLEX)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

macro(simple_fb_target name)
    BISON_TARGET(parser_${name} ${CMAKE_CURRENT_SOURCE_DIR}/${name}.y ${CMAKE_CURRENT_BINARY_DIR}/${name}.yy.cpp VERBOSE)
    FLEX_TARGET(scanner_${name} ${CMAKE_CURRENT_SOURCE_DIR}/${name}.l ${CMAKE_CURRENT_BINARY_DIR}/${name}.ll.cpp)
    ADD_FLEX_BISON_DEPENDENCY(scanner_${name} parser_${name})
endmacro(simple_fb_target)

macro(flex_executable name lexer)
    FLEX_TARGET(scanner_${name} ${CMAKE_CURRENT_SOURCE_DIR}/${lexer} ${CMAKE_CURRENT_BINARY_DIR}/${name}.ll.cpp)
    add_executable(${name} ${FLEX_scanner_${name}_OUTPUTS})
endmacro(flex_executable)


add_subdirectory(${PROJECT_SOURCE_DIR}/own)
add_subdirectory(${PROJECT_SOURCE_DIR}/book)

enable_testing()
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

file(GLOB_RECURSE TEST_FILES tests/main.cpp tests/*/*.cpp)
set(BOOST_INCLUDE_DIRS $boost_installation_prefix/include)
add_executable(unit ${SRC_FILES} ${TEST_FILES})

target_include_directories(unit PRIVATE ${SYMBOL_TABLE})
target_include_directories(unit PRIVATE ${AST})

target_include_directories(unit PRIVATE ${BOOST_INCLUDE_DIRS})
target_compile_definitions(unit PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(unit ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(unit unit)