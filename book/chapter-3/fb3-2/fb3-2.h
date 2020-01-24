//
// Created by pierreantoine on 11/01/2020.
//

#pragma once

#include <cstdlib>


typedef struct ast *astptr;
typedef struct symbol *symbolptr;
typedef struct symlist *symlistptr;

extern int yylineno;
void yyerror(const char *s, ...);

extern int yylex (void);

struct symbol
{
    char *name;
    double value;
    astptr func;
    symlistptr syms;
};

constexpr std::size_t NHASH = 9997;
extern struct symbol symtab[NHASH];

symbolptr lookup(char *);

struct symlist
{
    symbolptr sym;
    symlistptr next;
};

symlistptr newsymlist(symbolptr, symlistptr);
void symlistfree(symlistptr);

/**
 * node types:
 * 0-7 comparison ops
 * M unary minus
 * L expression or statement list
 * I IF
 * W WHILE
 * N symbol ref
 * = assignment
 * S list of symbols
 * F built in
 * C user function
 *
 */

enum bifs
{
    B_sqrt, B_exp, B_log, B_print,
};

struct ast
{
    int nodetype;
    astptr l;
    astptr d;
};

struct fncall
{
    int nodetype;
    astptr l;
    enum bifs functype;
};

struct ufncall
{
    int nodetype;
    astptr l;
    symbol *s;
};

struct flow
{
    int nodetype;
    astptr cond;
    astptr tl;
    astptr el;
};

struct numval
{
    int nodetype;
    double number;
};

struct symref
{
    int nodetype;
    symbolptr s;
};

struct symasgn
{
    int nodetype;
    symbolptr s;
    astptr v;
};

/**
 * Building functions
 */

astptr newast(int nodetype, astptr l, astptr r);
astptr newcmp(int cmptype, astptr l, astptr r);
astptr newfunc(int functype, astptr l);
astptr newcall(symbolptr s, astptr l);
astptr newref(symbolptr s);
astptr newasgn(symbolptr s, astptr v);
astptr newnum(double d);
astptr newflow(int nodetype, astptr cond, astptr tl, astptr tr);

void dodef(symbolptr name, symlistptr syms, astptr stmts);
double eval(astptr);
void treefree(astptr);