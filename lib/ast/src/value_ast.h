//
// Created by pierreantoine on 12/01/2020.
//


#pragma once


#include <iostream>
#include "ast.h"


namespace v1::ast::fb31
{
    template <typename T>
    class value_ast : public ast<T>
    {
    public:
        const T value;
        ~value_ast() override = default;
        T accept(ast_visitor<T> & visitor) override;
        T accept(ast_visitor<T> && visitor) override;

        value_ast(const T & value);
    };
}


template <typename T>
T v1::ast::fb31::value_ast<T>::accept(v1::ast::fb31::ast_visitor<T> & visitor)
{
    return visitor.visit(*this);
}

template <typename T>
T v1::ast::fb31::value_ast<T>::accept(v1::ast::fb31::ast_visitor<T> && visitor)
{
    return visitor.visit(*this);
}

template <typename T>
v1::ast::fb31::value_ast<T>::value_ast(const T & value)
        : value(value)
{
}