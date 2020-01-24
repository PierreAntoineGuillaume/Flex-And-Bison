//
// Created by pierreantoine on 11/01/2020.
//

#include "fb3-2.h"
#include <cstdio>
#include <cstdarg>

void yyerror(const char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}