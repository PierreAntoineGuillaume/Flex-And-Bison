
%option noyywrap nodefault yylineno case-insensitive

%{
    #include "src/ref.h"
    #include "src/reflist.h"
    #include "src/symbol.h"

    #include "src/lexer.h"
%}

%%

%%

int main ()
{
    lexer lexer;
    yylineno=1;
    lexer.lineno();
    lexer.lex();

}