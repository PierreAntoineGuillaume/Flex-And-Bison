
%{
#include <stdio.h>
#include <stdlib.h>
#include "fb3-1.h"
%}

%union {
    fb3_1::ast *a;
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
    printf("= %g\n", fb3_1::eval($2));
    fb3_1::treefree($2);
    printf("> ");
}
| calclist EOL {
    printf("> ");
}

exp: exp '+' exp { $$ = fb3_1::newast('+', $1, $3); }
| exp '-' exp { $$ = fb3_1::newast('-', $1, $3); }
| exp '*' exp { $$ = fb3_1::newast('*', $1, $3); }
| exp '/' exp { $$ = fb3_1::newast('/', $1, $3); }
| '|' exp { $$ = fb3_1::newast('|', $2, NULL); }
| '(' exp ')' { $$ = $2; }
| '-' exp %prec UMINUS { $$ = fb3_1::newast('M', $2, NULL); }
| NUMBER { $$ = fb3_1::newnum($1); }

%%

int main()
{
    yyparse();
    return 0;
}

