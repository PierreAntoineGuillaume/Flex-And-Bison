
simple_fb_target(fb3-2)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(fb3-2 ${BISON_parser_fb3-2_OUTPUTS} ${FLEX_scanner_fb3-2_OUTPUTS} fb3-2.cpp fb3-2.h)
target_sources(fb3-2 PUBLIC ${SRC_FILES})
target_include_directories(fb3-2 PUBLIC ${LEXING} ${AST})