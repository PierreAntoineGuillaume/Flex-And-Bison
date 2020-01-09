
%option noyywrap yylineno case-insensitive

%{
    #include "src/flex.h"
    #include "src/basic_lexer.h"

    basic_lexer lexer;
%}

WHITESPACES     [\n\r\t ]
NOT_WHITESPACES [^\n\r\t ]


%%

{WHITESPACES}      ;
{NOT_WHITESPACES}+       lexer.match(yytext);


%%


int main()
{
    lexer.lex();
}