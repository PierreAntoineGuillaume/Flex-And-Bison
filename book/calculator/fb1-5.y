%{
#include <stdio.h>

%}

%token NUMBER
%token ADD SUBSTRACT MULTIPLY DIVIDE ABSOLUTE
%token EOL

%%

calculation:
           | calculation addition EOL { printf ("= %d\n",$2); }
;

addition: factor
        | addition ADD factor        { $$ = $1 + $3; }
        | addition SUBSTRACT factor  { $$ = $1 - $3; }
;

factor: terminal
      | factor MULTIPLY terminal     { $$ = $1 * $3; } 
      | factor SUBSTRACT terminal    { $$ = $1 / $3; }
;

terminal: NUMBER
        | ABSOLUTE terminal { $$ = $2 > 0 ? $2 : -$2; }
;

%%

int main(){
    yyparse();
    return 0;
}

int yyerror(char *s){
    fprintf(stderr, "error: %s", s);
    return 0;
}
