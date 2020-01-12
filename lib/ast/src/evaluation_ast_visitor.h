//
// Created by pierreantoine on 12/01/2020.
//


#pragma once


#include <stdexcept>
#include "ast_visitor.h"
#include "value_ast.h"
#include "dual_ast.h"


namespace v1::ast::fb31
{
    template <typename T>
    class evaluation_ast_visitor : public ast_visitor<T>
    {
    public:
        T visit(value_ast<T> & ast) override;
        T visit(dual_ast<T> & ast) override;
        T visit(single_ast<T> & ast) override;

        ~evaluation_ast_visitor() override = default;
    };
}

template <typename T>
T v1::ast::fb31::evaluation_ast_visitor<T>::visit(v1::ast::fb31::value_ast<T> & ast)
{
    return ast.value;
}

template <typename T>
T v1::ast::fb31::evaluation_ast_visitor<T>::visit(v1::ast::fb31::dual_ast<T> & ast)
{
    switch (ast.symbol)
    {
        case '+': return (ast.left().accept(*this) + ast.right().accept(*this));
        case '-': return (ast.left().accept(*this) - ast.right().accept(*this));
        case '*': return (ast.left().accept(*this) * ast.right().accept(*this));
        case '/': {
            const auto& divider = ast.right().accept(*this);
            if (divider == 0) {
                throw std::runtime_error("zero division");
            }
            return (ast.left().accept(*this) / divider);
        }
        default:throw std::runtime_error("Unknown symbol " + ast.symbol);
    }
}

template <typename T>
T v1::ast::fb31::evaluation_ast_visitor<T>::visit(v1::ast::fb31::single_ast<T> & ast)
{
    switch (ast.symbol)
    {
        case 'M': return - ast.get_child().accept(*this);
        case '|': return abs(ast.get_child().accept(*this));
        default:throw std::runtime_error("Unknown symbol " + ast.symbol);
    }
}