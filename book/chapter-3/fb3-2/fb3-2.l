
%option noyywrap nodefault yylineno

%{
    #include "fb3-2.h"
    #include "fb3-2.yy.hpp"
    #define yield(item) printf(#item "\n"); return item;
%}

EXP         ([eE][+-]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
"{" |
"}" |
"(" |
")" {  yield(yytext[0]); }

">"         { yylval.fn = 1; yield(CMP); }
"<"         { yylval.fn = 2; yield(CMP); }
"<>" | "!=" { yylval.fn = 3; yield(CMP); }
"=="        { yylval.fn = 4; yield(CMP); }
">="        { yylval.fn = 5; yield(CMP); }
"<="        { yylval.fn = 6; yield(CMP); }

"if"        { yield(IF); }
"then"      { yield(THEN); }
"else"      { yield(ELSE); }
"while"     { yield(WHILE); }
"do"        { yield(DO); }
"let"       { yield(LET); }


"sqrt"      { yylval.fn = B_sqrt;  return FUNC; }
"exp"       { yylval.fn = B_exp;   return FUNC; }
"log"       { yylval.fn = B_log;   return FUNC; }
"echo"      { yylval.fn = B_print; return FUNC; }

[a-zA-Z][a-zA-Z0-9_]*     { yylval.s = lookup(yytext); yield(NAME); }

[0-9]+{EXP}? |
[0-9]+"."[0-9]*{EXP}? |
"."[0-9]*{EXP}? { yylval.d = atof(yytext); return NUMBER;}

"//".* ;

\\\n    { printf("> "); }
\n      { return EOL; }

[ \t]   ;
.       { yyerror("unknown character %s", yytext); }

%%