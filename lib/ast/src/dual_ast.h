//
// Created by pierreantoine on 12/01/2020.
//


#pragma once


#include <memory>
#include "ast.h"

namespace v1::ast::fb31
{
    template <typename T>
    class dual_ast : public ast<T>
    {
       typedef std::shared_ptr<ast<T>> astptr;
        astptr left_child;
        astptr right_child;
    public:
        const unsigned char symbol;
        ~dual_ast() override = default;
        T accept(ast_visitor<T> & visitor) override;

        dual_ast(unsigned char symbol, astptr left, astptr right);

        ast<T> & left();
        ast<T> & right();
    };
}

template <typename T>
T v1::ast::fb31::dual_ast<T>::accept(v1::ast::fb31::ast_visitor<T> & visitor)
{
    return visitor.visit(*this);
}

template <typename T>
v1::ast::fb31::dual_ast<T>::dual_ast(unsigned char symbol, astptr left, astptr right)
        :   ast<T>(), left_child(left), right_child(right), symbol(symbol)
{

}

template <typename T>
v1::ast::fb31::ast<T> & v1::ast::fb31::dual_ast<T>::left()
{
    return *left_child;
}
template <typename T>
v1::ast::fb31::ast<T> & v1::ast::fb31::dual_ast<T>::right()
{
    return *right_child;
}
