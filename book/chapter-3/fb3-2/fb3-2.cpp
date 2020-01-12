//
// Created by pierreantoine on 11/01/2020.
//

#include <stdio.h>
#include <stdarg.h>
#include <src/flex.h>

void yyerror(const char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}