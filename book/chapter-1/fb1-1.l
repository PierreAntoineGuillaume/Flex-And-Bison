
%option noyywrap

%%


"+"    printf("PLUS\n");
"-"    printf("MINUS\n");
"*"    printf("MULTIPIED BY\n");
"/"    printf("DIVIDED BY\n");
\n     printf("NEWLINE\n");
[ \t]     ;
[0-9]+ printf("NUMBER %s\n",yytext);
.      printf("Unmatched character %s\n",yytext);
%%

