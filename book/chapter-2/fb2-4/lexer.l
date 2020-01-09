
%option noyywrap yylineno case-insensitive

%{
    #include "src/flex.h"
    #include "src/reference_lexer.h"

    reference_lexer lexer;
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