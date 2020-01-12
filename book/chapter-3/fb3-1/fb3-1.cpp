//
// Created by pierreantoine on 11/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "fb3-1.h"



fb3_1::ast * fb3_1::newast(int nodetype, fb3_1::ast *l, fb3_1::ast *r)
{
    fb3_1::ast *a = static_cast<fb3_1::ast *>(malloc(sizeof(fb3_1::ast)));
    if (!a)
    {
        ::yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

fb3_1::ast * fb3_1::newnum(double d)
{
    fb3_1::numval *a = static_cast<fb3_1::numval *>(malloc(sizeof(fb3_1::numval)));
    if (!a)
    {
        ::yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = d;
    return (fb3_1::ast *) a;
}

double fb3_1::eval(fb3_1::ast *a)
{
    switch (a->nodetype)
    {
        default: printf("internal error: fb3_1::eval bad node %c\n", a->nodetype);
            return 0.;

        case 'K': return ((fb3_1::numval *) a)->number;

        case '+': return fb3_1::eval(a->l) + fb3_1::eval(a->r);
        case '-': return fb3_1::eval(a->l) - fb3_1::eval(a->r);
        case '*': return fb3_1::eval(a->l) * fb3_1::eval(a->r);
        case '/': return fb3_1::eval(a->l) / fb3_1::eval(a->r);
        case '|':
        {
            double d = fb3_1::eval(a->l);
            if (d < 0)
            {
                return -d;
            }
            return d;
        }
        case 'M': return -fb3_1::eval(a->l);
    }
}

void fb3_1::treefree(fb3_1::ast *a)
{
    switch (a->nodetype)
    {
        default: printf("internal error: free bad node %c\n", a->nodetype);
            break;
        case '+':
        case '-':
        case '*':
        case '/':fb3_1::treefree(a->r);
            [[fallthrough]];
        case '|':
        case 'M':
            fb3_1::treefree(a->l);
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