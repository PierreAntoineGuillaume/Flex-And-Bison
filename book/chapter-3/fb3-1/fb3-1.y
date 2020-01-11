
%{
#include <stdio.h>
#include <stdlib.h>
#include "fb3-1.h"
%}

%union {
    ast *a;
    double d;
}

%token <d> NUMBER
%token EOL
%type <a> exp

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%%

calclist:
| calclist exp EOL {
    printf("= %g\n", eval($2));
    treefree($2);
    printf("> ");
}
| calclist EOL {
    printf("> ");
}

exp: exp '+' exp { $$ = newast('+', $1, $3); }
| exp '-' exp { $$ = newast('-', $1, $3); }
| exp '*' exp { $$ = newast('*', $1, $3); }
| exp '/' exp { $$ = newast('/', $1, $3); }
| '|' exp { $$ = newast('|', $2, NULL); }
| '(' exp ')' { $$ = $2; }
| '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
| NUMBER { $$ = newnum($1); }

%%

int main()
{
    yyparse();
    return 0;
}

