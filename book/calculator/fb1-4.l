%{
        enum yytokentype {
            NUMBER=258,
            ADD,
            SUBSTRACT,
            MULTIPLY,
            DIVIDE,
            ABSOLUTE,
            EOL
        };
    
    int yylval;
%}

%option noyywrap

%%

"+"     return ADD;
"-"     return SUBSTRACT;
"*"     return MULTIPLY;
"/"     return DIVIDE;
"|"     return ABSOLUTE;
[0-9]+  { yylval = atoi(yytext); return NUMBER;}
\n      return EOL;
[ \t]   ;
.       { printf("Unmatched character %c\n",*yytext); }

%%

int main(int argc, char ** argv)
{
    int tok;

    while (tok = yylex())
    {
        printf("%d",tok);
        if (tok == NUMBER)
            printf(" = %d\n",yylval);
        else
            printf("\n");
    }
    return 0;
}
