//
// Created by pierreantoine on 12/01/2020.
//


#pragma once

namespace v1::ast::fb31
{

    template <typename T>
    class ast_visitor;

    template <typename T>
    class ast
    {
    public:
        virtual ~ast() = default;
        virtual T accept(ast_visitor<T> & visitor) = 0;
    };
}