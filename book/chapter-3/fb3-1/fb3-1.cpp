//
// Created by pierreantoine on 11/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "fb3-1.h"


ast *newast(int nodetype, ast *l, ast *r)
{
    ast *a = static_cast<ast *>(malloc(sizeof(ast)));
    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

ast *newnum(double d)
{
    numval *a = static_cast<numval *>(malloc(sizeof(numval)));
    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = d;
    return (ast *) a;
}

double eval(ast *a)
{
    switch (a->nodetype)
    {
        default: printf("internal error: eval bad node %c\n", a->nodetype);
            return 0.;

        case 'K': return ((numval *) a)->number;

        case '+': return eval(a->l) + eval(a->r);
        case '-': return eval(a->l) - eval(a->r);
        case '*': return eval(a->l) * eval(a->r);
        case '/': return eval(a->l) / eval(a->r);
        case '|':
        {
            double d = eval(a->l);
            if (d < 0)
            {
                return -d;
            }
            return d;
        }
        case 'M': return -eval(a->l);
    }
}

void treefree(ast *a)
{
    switch (a->nodetype)
    {
        default: printf("internal error: free bad node %c\n", a->nodetype);
            break;
        case '+':
        case '-':
        case '*':
        case '/':treefree(a->r);
            [[fallthrough]];
        case '|':
        case 'M':
            treefree(a->l);
            [[fallthrough]];
        case 'K':
            free(a);
    }
}

void yyerror(const char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}