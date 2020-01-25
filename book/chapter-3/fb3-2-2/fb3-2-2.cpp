//
// Created by pierreantoine on 11/01/2020.
//

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cmath>
#include "fb3-2-2.h"


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
    fprintf(stderr, "%s:%d: error: ", filename.c_str(), yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

void assert_not_null(void *pointer)
{
    if (!pointer)
    {
        yyerror("out of space");
        exit(1);
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

        case '=':
            treefree(((struct symasgn *) a)->v);
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

double eval_if(struct flow *ast);
double eval_while(struct flow *ast);
double callbuiltin(struct fncall *ast);
double calluser(struct ufncall *ast);
double read_number(struct numval *a);
void reset_old_values(unsigned int nargs, const double *oldval, symlistptr sl);
double eval(astptr a)
{
    if (!a)
    {
        return 0.0;
    }

    switch (a->nodetype)
    {
        case 'K':
            return read_number((struct numval *) a);
        case 'N':
            return ((struct symref *) a)->s->value;
        case '=':
            return ((struct symasgn *) a)->s->value = eval(((struct symasgn *) a)->v);
        case '+':
            return eval(a->l) + eval(a->r);
        case '-':
            return eval(a->l) - eval(a->r);
        case '*':
            return eval(a->l) * eval(a->r);
        case '/':
            return eval(a->l) / eval(a->r);
        case '|':
            return std::abs(eval(a->l));
        case 'M':
            return -eval(a->l);
        case '1':
            return eval(a->l) > eval(a->r);
        case '2':
            return eval(a->l) < eval(a->r);
        case '3':
            return eval(a->l) != eval(a->r);
        case '4':
            return eval(a->l) == eval(a->r);
        case '5':
            return eval(a->l) >= eval(a->r);
        case '6':
            return eval(a->l) <= eval(a->r);

        case 'I':
            return eval_if((struct flow *) a);
        case 'W':
            return eval_while((struct flow *) a);

        case 'L':
            eval(a->l);
            return eval(a->r);
        case 'F':
            return callbuiltin((struct fncall *) a);
        case 'C':
            return calluser((struct ufncall *) a);
        default:
            printf("internal error: bad node %c\n", a->nodetype);
    }
    return 0;
}

double read_number(struct numval *a)
{
    return a->number;
}

double eval_if(struct flow *ast)
{
    if (eval(ast->cond) != 0)
    {
        return eval(ast->tl);
    }
    return eval(ast->el);
}

double eval_while(struct flow *ast)
{
    if (!ast->tl)
    {
        return 0;
    }
    double v = 0;
    while (eval(ast->cond) != 0)
    {
        v = eval(ast->tl);
    }
    return v;
}

double callbuiltin(struct fncall *ast)
{
    double v = eval(ast->l);
    switch (ast->functype)
    {
        case bifs::B_sqrt:
            return std::sqrt(v);
        case bifs::B_exp:
            return std::exp(v);
        case bifs::B_log:
            return std::log(v);
        case bifs::B_print:
            printf("echo (%g)\n", v);
            return v;
    }
    yyerror("unknown built-in call with key: %d", ast->functype);
    return 0;
}

void dodef(symbolptr name, symlistptr syms, astptr func)
{
    if (name->syms)
    {
        symlistfree(name->syms);
    }
    name->syms = syms;
    if (name->func)
    {
        treefree(name->func);
    }
    name->func = func;
}

unsigned count_args(symlistptr list)
{
    unsigned count;
    for (count = 0; list; list = list->next)
    {
        count += 1;
    }
    return count;
}

double *double_malloc(unsigned size)
{
    auto d = (double *) malloc(size * sizeof(double));
    assert_not_null(d);
    return d;
}
void save_and_update_values(symlistptr sl, unsigned int size, double *memory, const double *new_values);
void reset_old_values(symlistptr, unsigned int, const double *);

double calluser(struct ufncall *ast)
{
    auto fn = ast->s;
    if (!fn->func)
    {
        yyerror("call to undefined function %s\n", fn->name);
        return 0;
    }
    auto args = ast->l;
    unsigned nargs = count_args(fn->syms);
    auto oldval = double_malloc(nargs);
    auto newval = double_malloc(nargs);

    for (unsigned i = 0; i < nargs; ++i)
    {
        if (!args)
        {
            yyerror("too few arguments in call to %s", fn->name);
            free(oldval);
            free(newval);
            return 0;
        }
        if (args->nodetype == 'L')
        {
            newval[i] = eval(args->l);
            args = args->r;
            continue;
        }
        newval[i] = eval(args);
        args = nullptr;
    }

    save_and_update_values(fn->syms, nargs, oldval, newval);
    free(newval);
    double v = eval(fn->func);

    reset_old_values(fn->syms, nargs, oldval);
    free(oldval);
    return v;
}

void save_and_update_values(symlistptr sl, unsigned int size, double *memory, const double *new_values)
{
    for (unsigned i = 0; i < size; ++i)
    {
        memory[i] = sl->sym->value;
        sl->sym->value = new_values[i];
        sl = sl->next;
    }
}

void reset_old_values(symlistptr sl, unsigned int size, const double *old_values)
{
    for (unsigned i = 0; i < size; ++i)
    {
        sl->sym->value = old_values[i];
        sl = sl->next;
    }
}
