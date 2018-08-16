%{
#include "fb1-5.tab.h"
%}

%%

"+"     return ADD;
"-"     return SUBSTRACT;
"*"     return MULTIPLY;
"/"     return DIVIDE;
"|"     return ABSOLUTE;
0x[0-9A-F]+ { yylval = strtol(yytext, NULL, 16); return NUMBER; }
[0-9]+  { yylval = atoi(yytext); return NUMBER;}
"//".*|"\n"      return EOL;
[ \t]   ;
.       { printf("Unmatched character %c\n",*yytext); }

%%
