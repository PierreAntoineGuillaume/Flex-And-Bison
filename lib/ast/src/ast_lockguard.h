//
// Created by pierreantoine on 12/01/2020.
//


#pragma once


#include "ast.h"


namespace v1::ast::fb31
{
    template <typename T>
    class ast_lockguard
    {
        typedef v1::ast::fb31::ast<T> *ast_ptr;
        ast_ptr ast;
    public:
        ast_lockguard(ast_ptr ast);
        ast_lockguard(const ast_lockguard &) = delete;
        ast_lockguard(ast_lockguard && other);
        ~ast_lockguard();
    };
}

template <typename T>
v1::ast::fb31::ast_lockguard<T>::ast_lockguard(ast_ptr ast)
        : ast(ast)
{

}
template <typename T>
v1::ast::fb31::ast_lockguard<T>::~ast_lockguard()
{
    if (ast)
    {
        delete ast;
    }
}
template <typename T>
v1::ast::fb31::ast_lockguard<T>::ast_lockguard(v1::ast::fb31::ast_lockguard<T> && other)
        : ast(other.ast)
{
    other.ast = nullptr;
}
