find_package(FLEX)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

flex_executable(wc wc.l)
flex_executable(fb2-2 wc.l)

flex_executable(fb2-3 fb2-3/lexer.l)

flex_executable(fb2-4 fb2-4/lexer.l)
target_sources(fb2-4 PUBLIC ${SRC_FILES}
        fb2-4/reference_lexer.cpp
        fb2-4/reference_lexer.h
        )

target_include_directories(fb2-4 PUBLIC ../../lib/symbol_table ../../lib/lexing fb2-4)
