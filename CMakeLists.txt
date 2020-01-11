cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra --pedantic -Werror -fconcepts")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment -Wno-unused-function")

project(Flex-And-Bison)

add_subdirectory(${PROJECT_SOURCE_DIR}/book/chapter-1)
add_subdirectory(${PROJECT_SOURCE_DIR}/book/chapter-2)
add_subdirectory(${PROJECT_SOURCE_DIR}/own/phptools)
