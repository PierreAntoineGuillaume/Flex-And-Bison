//
// Created by pierreantoine on 11/01/2020.
//

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "fb3-2.h"


struct symbol symtab[NHASH];

static unsigned symhash(const char *sym)
{
    unsigned int hash = 0;
    unsigned c;
    while ((c = *(sym++)))
    {
        hash = hash * 9 ^ c;
    }
    return hash;
}

symbolptr lookup(char *name)
{
    symbolptr sp = &symtab[symhash(name) % NHASH];
    int scount = NHASH;
    while (--scount >= 0)
    {
        if (sp->name && !strcmp(sp->name, name))
        {
            return sp;
        }

        if (!sp->name)
        {
            sp->name = strdup(name);
            sp->value = 0;
            sp->func = nullptr;
            sp->syms = nullptr;
            return sp;
        }

        if (++sp >= symtab + NHASH)
        {
            sp = symtab;
        }
    }
    yyerror("symbol table overflow");
    abort();
}

void yyerror(const char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}