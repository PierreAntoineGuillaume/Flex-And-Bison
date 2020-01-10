
%option noyywrap yylineno case-insensitive

%{
    #include "src/flex.h"
    #include "src/reference_lexer.h"

    reference_lexer lexer;
%}
NEWLINE             [\n\r]+
WHITESPACE         [\t ]
LETTERS               [a-zA-ZéèœæôêëàùûâîçïüÉÔÈÙÀÎÊËÇÏÜÂŒÆ]
REST                .

%%

"le"|"les"|"je"|"de"|"s"|"l"|"sa"|"aux"|"au"|"du"|"ne"|"ce"|"que"|"à"|"a"|"c"|"un"|"une"|"la"|"ô"|"toi"|"mon"|"d"    lexer.skip(yytext);
{WHITESPACE}|[-—,.':«»;()!?]|"’"|"…"            lexer.skip(yytext);
{NEWLINE}               lexer.resetColumn();
{LETTERS}+              lexer.match(yytext);
.                       throw std::runtime_error("bad symbol" + std::string(yytext));

%%

#include <vector>
#include <iostream>

int main(int argc, char** argv)
{
    try
    {
        if (argc < 2)
            {
                lexer.lexSTDIN();
                lexer.display_table();
                return 0;
            }

            std::vector<std::string> arguments(argv+1, argv+argc);

            for (const auto &file:arguments)
            {
                FILE *handle = fopen(file.c_str(), "r");
                if (!handle)
                {
                    throw new std::runtime_error("could not open file: " + file);
                }

                lexer.lexFile(file.c_str(), handle);
                fclose(handle);
            }

            lexer.display_table();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}