
%option noyywrap nodefault yylineno

%{
    #include "fb3-2.h"
    #include "fb3-2.yy.hpp"
%}

EXP ([eE][+-]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"%" |
"|" |
"(" |
")" { return yytext[0]; }

[0-9]+{EXP}? |
[0-9]+"."[0-9]*{EXP}? |
"."[0-9]*{EXP}? { yylval.d = atof(yytext); return NUMBER;}

\n { return EOL; }
"//".* ;

[ \t]   ;
.       { yyerror("unknown character %c", *yytext); }

%%