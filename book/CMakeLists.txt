
find_package(FLEX)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

macro(flex_executable name lexer)
    FLEX_TARGET(scanner_${name} ${CMAKE_CURRENT_SOURCE_DIR}/${lexer} ${CMAKE_CURRENT_BINARY_DIR}/${name}.ll.cpp)
    add_executable(${name} ${FLEX_scanner_${name}_OUTPUTS})
endmacro(flex_executable)

macro(simple_fb_target name)
    BISON_TARGET(parser_${name} ${CMAKE_CURRENT_SOURCE_DIR}/${name}.y ${CMAKE_CURRENT_BINARY_DIR}/${name}.yy.cpp VERBOSE)
    FLEX_TARGET(scanner_${name} ${CMAKE_CURRENT_SOURCE_DIR}/${name}.l ${CMAKE_CURRENT_BINARY_DIR}/${name}.ll.cpp)
    ADD_FLEX_BISON_DEPENDENCY(scanner_${name} parser_${name})
endmacro(simple_fb_target)

add_subdirectory(chapter-1)
add_subdirectory(chapter-2)
add_subdirectory(chapter-3)

