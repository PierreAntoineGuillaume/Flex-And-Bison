%{
#include <stdio.h>

int yylex();
void yyerror (char const *s)
{
    fprintf(stderr, "Error in bison : %s\n", s);
}

%}

%token NUMBER
%token ADD SUBSTRACT MULTIPLY DIVIDE ABSOLUTE BINARY_AND
%token EOL

%%

calculation: /* empty */
 | calculation EOL
 | calculation addition EOL { printf ("= %d\n",$2); }
;

addition: factor
 | addition ADD factor        { $$ = $1 + $3; }
 | addition SUBSTRACT factor  { $$ = $1 - $3; }
 | addition ABSOLUTE factor   { $$ = $1 | $3; }
 | addition BINARY_AND factor { $$ = $1 & $3; }
;

factor: terminal
 | factor MULTIPLY terminal     { $$ = $1 * $3; } 
 | factor DIVIDE terminal    { $$ = $1 / $3; }
;

terminal: NUMBER
 | ABSOLUTE NUMBER { $$ = $2 > 0 ? $2 : -$2; }
;

%%

int main(){
    yyparse();
    return 0;
}

