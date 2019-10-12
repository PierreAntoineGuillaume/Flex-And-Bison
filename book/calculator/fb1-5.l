%{

    #include "fb1-5.yy.hpp"

%}

%option noyywrap

%%

"+"     return ADD;
"-"     return SUBSTRACT;
"*"     return MULTIPLY;
"/"     return DIVIDE;
"|"     return ABSOLUTE;
"&"     return BINARY_AND;
"("     return OPEN_P;
")"     return CLOSE_P;
"^"     return POWK;



0x[0-9A-F]+   { yylval = strtol(yytext, NULL, 16); return NUMBER; }
0b[01]+       { yylval = strtol(yytext+2, NULL, 2); return NUMBER; }
0[0-8]+       { yylval = strtol(yytext, NULL, 8); return NUMBER; }
[0-9]+        { yylval = atoi(yytext); return NUMBER;}
"//".*|"\n"   return EOL;
[ \t]         ;
"//".*
.             { return ERR_TOKEN; }

%%
