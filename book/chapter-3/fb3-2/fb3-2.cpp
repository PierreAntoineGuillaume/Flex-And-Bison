//
// Created by pierreantoine on 11/01/2020.
//

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "fb3-2.h"


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
symbolptr symbol_lookup(symbolptr map, const unsigned map_size, char *name)
{
    symbolptr sp = &map[symhash(name) % map_size];
    int scount = map_size;
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

        if (++sp >= map + map_size)
        {
            sp = map;
        }
    }
    yyerror("symbol table overflow");
    abort();
}

struct symbol symtab[NHASH];
symbolptr lookup(char *name)
{
    return symbol_lookup(symtab, NHASH, name);
}

void yyerror(const char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

void assert_not_null(void *pointer)
{
    if (!pointer)
    {
        yyerror("out of space");
        exit(0);
    }
}

astptr ast_malloc()
{
    auto a = (astptr) malloc(sizeof(struct ast));
    assert_not_null(a);
    return a;
}

astptr newast(int nodetype, astptr l, astptr r)
{
    astptr a = ast_malloc();
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

astptr newnum(double d)
{
    struct numval *a = (struct numval *) malloc(sizeof(struct numval));
    assert_not_null(a);
    a->nodetype = 'K';
    a->number = d;
    return (astptr) a;
}

astptr newcmp(int cmptype, astptr l, astptr r)
{
    auto a = ast_malloc();
    a->nodetype = '0' + cmptype;
    a->l = l;
    a->r = r;
    return a;
}

astptr newfunc(enum bifs functype, astptr l)
{
    auto a = (struct fncall *) malloc(sizeof(struct fncall *));
    assert_not_null(a);
    a->nodetype = 'F';
    a->l = l;
    a->functype = functype;
    return (astptr) a;
}

astptr newcall(symbolptr s, astptr l)
{
    auto a = (struct ufncall *) malloc(sizeof(struct ufncall));
    assert_not_null(a);
    a->nodetype = 'C';
    a->l = l;
    a->s = s;
    return (astptr) a;
}

astptr newref(symbolptr s)
{
    auto a = (struct symref *) malloc(sizeof(struct symref));
    assert_not_null(a);
    a->nodetype = 'N';
    a->s = s;
    return (astptr) a;
}

astptr newasgn(symbolptr s, astptr v)
{
    auto a = (struct symasgn *) malloc(sizeof(struct symasgn));
    a->nodetype = '=';
    a->s = s;
    a->v = v;
    return (astptr) a;
}

astptr newflow(int nodetype, astptr cond, astptr tl, astptr el)
{
    auto a = (struct flow *) malloc(sizeof(struct flow));
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (astptr) a;
}

void treefree(astptr a)
{
    if (!a)
    {
        return;
    }
    switch (a->nodetype)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case 'L':
            treefree(a->r);
            [[fallthrough]];
        case '|':
        case 'M':
        case 'C':
        case 'F':
            treefree(a->l);
            [[fallthrough]];
        case 'K':
        case 'N':
            break;

        case 'I' :
        case 'W':
            treefree(((struct flow *) a)->cond);
            treefree(((struct flow *) a)->tl);
            treefree(((struct flow *) a)->el);
            break;
        default:
            printf("internal error: free bad node %c\n", a->nodetype);
    }
    free(a);
}

symlistptr newsymlist(symbolptr sym, symlistptr next)
{
    auto sl = (struct symlist *) malloc(sizeof(struct symlist));
    assert_not_null(sl);
    sl->sym = sym;
    sl->next = next;
    return sl;
}
void symlistfree(symlistptr sl)
{
    while (sl)
    {
        auto nsl = sl->next;
        free(sl);
        sl = nsl;
    }
}


void dodef(symbolptr, symlistptr, astptr)
{

}

double eval(astptr)
{
    return 0.;
}