
%{

#include <cstdio>
#include <cstdlib>
#include "fb3-2-2.h"
#include <string>

std::string filename;
%}

%define parse.trace

%union {
    astptr a;
    double d;
    symbolptr s;
    symlistptr sl;
    int fn;
}


%token <d> NUMBER
%token <s> NAME
%token <fn> FUNC
%token IF THEN ELSE WHILE DO LET EOL
%token EOFILE 0
%token DISABLE ENABLE DEBUGGING

%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist
%type <sl> symlist

%start calclist

%%

stmt: IF '(' exp ')' '{' list '}'                       { $$ = newflow('I', $3, $6, NULL); }
    | IF '(' exp ')' '{' list '}' ELSE '{' list '}'     { $$ = newflow('I', $3, $6, $10); }
    | WHILE '(' exp ')' '{' list '}'                    { $$ = newflow('W', $3, $6, NULL); }
    | exp
;
list:  /* nothing */ { $$ = NULL; }
    | stmt ';' list {
        if ($3 == NULL) {
            $$ = $1;
        } else {
            $$ = newast('L', $1, $3);
        }
    }
;

exp: exp CMP exp        { $$ = newcmp($2, $1, $3); }
| exp '+' exp           { $$ = newast('+', $1, $3); }
| exp '-' exp           { $$ = newast('-', $1, $3); }
| exp '*' exp           { $$ = newast('*', $1, $3); }
| exp '/' exp           { $$ = newast('/', $1, $3); }
| '|' exp               { $$ = newast('|', $2, NULL); }
| '(' exp ')'           { $$ = $2; }
| '-' exp %prec UMINUS  { $$ = newast('M', $2, NULL); }
| NUMBER                { $$ = newnum($1); }
| NAME                  { $$ = newref($1); }
| NAME '=' exp          { $$ = newasgn($1, $3); }
| FUNC '(' explist ')'  { $$ = newfunc(static_cast<enum bifs>($1), $3); }
| NAME '(' explist ')'  { $$ = newcall($1, $3); }
;

explist: exp
| exp ',' explist   { $$ = newast('L', $1, $3); }
;

symlist:NAME        { $$ = newsymlist($1, NULL); }
| NAME ',' symlist  { $$ = newsymlist($1, $3); }
;

end: EOL
| EOFILE

calclist:                                           ;
| calclist directive end
| calclist stmt end                                 { printf("= %g\n> ", eval($2)); treefree($2); }
| calclist LET NAME '(' symlist ')' '=' list end    {
    dodef($3, $5, $8);
    printf("Defined %s\n>", $3->name);
}
| calclist error end                                { yyerrok; printf("\n> ");}
;


directive: ENABLE DEBUGGING     { yydebug = 1; }
| DISABLE DEBUGGING             { yydebug = 0; }

%%

#include <vector>
#include <string>

int main(int argc, char **argv)
{
    std::vector<std::string> arguments(argv+1, argv+argc);
    if (arguments.size() < 1)
    {
        yyparse();
        return 0;
    }
    for (const auto &file:arguments)
    {
        FILE *handle = fopen(file.c_str(), "r");
        if (!handle)
        {
            perror("bad file");
            exit(1);
        }
        filename = file;
        yylineno=1;
        yyrestart(handle);
        yyparse();
        fclose(handle);
    }
    return 0;
}

