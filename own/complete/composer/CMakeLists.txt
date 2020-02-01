


simple_fb_target(composer)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(composer ${BISON_parser_composer_OUTPUTS} ${FLEX_scanner_composer_OUTPUTS} composer.cpp composer.h)