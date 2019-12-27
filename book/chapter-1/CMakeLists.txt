find_package(BISON)
find_package(FLEX)


BISON_TARGET(parser ${CMAKE_CURRENT_SOURCE_DIR}/fb1-5.y ${CMAKE_CURRENT_BINARY_DIR}/fb1-5.yy.cpp)
FLEX_TARGET(scanner ${CMAKE_CURRENT_SOURCE_DIR}/fb1-5.l ${CMAKE_CURRENT_BINARY_DIR}/fb1-5.ll.cpp)

ADD_FLEX_BISON_DEPENDENCY(scanner parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(fb1-5 ${BISON_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS})
