//
// Created by pierreantoine on 11/01/2020.
//

#pragma once


#include "src/flex.h"

namespace fb3_1
{

    typedef struct ast
    {
        int nodetype;
        ast *l;
        ast *r;
    } ast;

    typedef struct numval
    {
        int nodetype;
        double number;
    } numval;

    ast *newast(int nodetype, ast *l, ast *r);
    ast *newnum(double d);

    double eval(ast *);
    void treefree(ast *);
}