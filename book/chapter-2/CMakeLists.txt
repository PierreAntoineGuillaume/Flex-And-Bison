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
        lib/symbol_table/src/reference.h
        lib/symbol_table/src/reference.cpp
        lib/symbol_table/src/symbol.h
        lib/symbol_table/src/symbol.cpp
        lib/symbol_table/src/symbol_catalog.cpp
        lib/symbol_table/src/symbol_catalog.h
        lib/symbol_table/src/symbol_manager.hpp

        lib/lexing/src/reference_lexer.cpp
        lib/lexing/src/reference_lexer.h
        lib/lexing/src/lexer_interface.h
        lib/lexing/src/flex.h
        )

target_include_directories(fb2-4 PUBLIC lib/symbol_table lib/lexing fb2-4)
