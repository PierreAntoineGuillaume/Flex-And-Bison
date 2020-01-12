
%{
#include "fb3-1-2.h"
%}

%union {
    astptr a;
    double d;
}

%token <d> NUMBER
%token EOL
%type <a> exp

%left '+' '-'
%left '*' '/' '%'
%nonassoc '|' UMINUS

%%

calclist:
| calclist exp EOL {
    try
    {
        auto guard = ast_lockguard($2);
        printf("= %g\n", $2->accept(eval()));
    } catch (const std::runtime_error & error)
    {
        std::cerr << "Runtime Error : " << error.what() << "\n";
    }
    printf("> ");
}
| calclist EOL {
    printf("> ");
}

exp: exp '+' exp { $$ = new d_ast($1,'+', $3); }
| exp '-' exp { $$ = new d_ast($1,'-', $3); }
| exp '*' exp { $$ = new d_ast($1,'*', $3); }
| exp '/' exp { $$ = new d_ast($1,'/', $3); }
| exp '%' exp { $$ = new d_ast($1,'%', $3); }
| '|' exp { $$ = new s_ast('|', $2); }
| '(' exp ')' { $$ = $2; }
| '-' exp %prec UMINUS { $$ = new s_ast('M', $2); }
| NUMBER { $$ = new val_ast($1); }

%%

int main()
{
    yyparse();
    return 0;
}

