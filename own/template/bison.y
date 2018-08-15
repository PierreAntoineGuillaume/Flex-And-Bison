%{
#include <stdio.h>

int yylex();
void yyerror (char const *s)
{
    fprintf(stderr, "Error in parser : %s\n", s);
}

%}

%token EXAMPLE

%%


terminal: EXEMPLE NUMBER { $$ = $2 > 0 ? $2 : -$2; }
;

%%

int main(){
    yyparse();
    return 0;
}

