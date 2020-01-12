
simple_fb_target(fb3-1)

file(GLOB_RECURSE FB3-1 ./*.cpp ./*.h)
file(GLOB_RECURSE HEADERS ./*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(fb3-1 ${BISON_parser_fb3-1_OUTPUTS} ${FLEX_scanner_fb3-1_OUTPUTS} ${HEADERS})
target_sources(fb3-1 PUBLIC ${SRC_FILES} ${FB3-1})
target_include_directories(fb3-1 PUBLIC ${LEXING})