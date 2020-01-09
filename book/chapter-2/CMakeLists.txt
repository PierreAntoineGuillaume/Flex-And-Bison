find_package(FLEX)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

macro(flex_executable name lexer)
    FLEX_TARGET(scanner_${name} ${CMAKE_CURRENT_SOURCE_DIR}/${lexer} ${CMAKE_CURRENT_BINARY_DIR}/${name}.ll.cpp)
    add_executable(${name} ${FLEX_scanner_${name}_OUTPUTS})
endmacro(flex_executable)

flex_executable(wc wc.l)
flex_executable(fb2-2 wc.l)

flex_executable(fb2-3 fb2-3/lexer.l)

flex_executable(fb2-4 fb2-4/lexer.l)
target_sources(fb2-4 PUBLIC
        lib/symbol_table/src/ref.h
        lib/symbol_table/src/ref.cpp
        lib/symbol_table/src/reflist.h
        lib/symbol_table/src/reflist.cpp
        lib/symbol_table/src/symbol.h
        lib/symbol_table/src/symbol.cpp

        lib/lexing/src/lexer.cpp
        lib/lexing/src/lexer.h
        lib/lexing/src/flex.h
        )

target_include_directories(fb2-4 PUBLIC lib/symbol_table lib/lexing)
