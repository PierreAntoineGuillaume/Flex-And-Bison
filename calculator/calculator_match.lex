%%
"+"    printf("PLUS\n");
"-"    printf("MINUS\n");
"*"    printf("MULTIPIED BY\n");
"/"    printf("DIVIDED BY\n");
\n     printf("NEWLINE\n");
\s     ;
[0-9]+ printf("NUMBER %d\n",yytext);
.      printf("Unmatched character %s\n",yytext);
%%

