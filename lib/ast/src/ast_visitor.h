//
// Created by pierreantoine on 12/01/2020.
//


#pragma once


#include "value_ast.h"
#include "dual_ast.h"
#include "single_ast.h"

namespace v1::ast::fb31
{

    template <typename T>
    class ast_visitor
    {
    public:
        virtual T visit(value_ast<T> & ast) = 0;
        virtual T visit(dual_ast<T> & ast) = 0;
        virtual T visit(single_ast<T> & ast) = 0;
        virtual ~ast_visitor() = default;
    };
}