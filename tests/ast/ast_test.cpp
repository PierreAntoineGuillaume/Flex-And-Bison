//
// Created by pierreantoine on 12/01/2020.
//


#include <boost/test/unit_test.hpp>
#include <memory>
#include "src/value_ast.h"
#include "src/single_ast.h"
#include "src/dual_ast.h"
#include "src/evaluation_ast_visitor.h"
#include "src/ast_lockguard.h"


using namespace v1::ast::fb31;

typedef value_ast<double> val_ast;
typedef val_ast *ast_ptr;
typedef single_ast<double> s_ast;
typedef dual_ast<double> d_ast;
typedef evaluation_ast_visitor<double> eval;

BOOST_AUTO_TEST_CASE(DOUBLE_AST)
{
    std::list<ast_lockguard<double>> ptr_list;

    auto auto_free_val = [&](double d)
    {
        auto pointer = new val_ast(d);
        ptr_list.emplace_back(ast_lockguard<double>(pointer));
        return pointer;
    };

    auto val = [](double d){
        return new val_ast(d);
    };

    BOOST_CHECK_EQUAL( 5, auto_free_val(5)->accept(eval()));
    BOOST_CHECK_EQUAL(-5, auto_free_val(-5)->accept(eval()));
    BOOST_CHECK_EQUAL(-5, s_ast('M', val(5.f)).accept(eval()));
    BOOST_CHECK_EQUAL( 5, s_ast('M', val(-5.f)).accept(eval()));
    BOOST_CHECK_EQUAL(10, d_ast(val(5), '-', val(-5)).accept(eval()));

    try
    {
        d_ast(val(0), '/', val(0)).accept(eval());
        BOOST_ERROR("No exception thrown on zero division");
    }
    catch (const std::runtime_error & e)
    {
        BOOST_CHECK(strcmp(e.what(), "zero division") == 0);
    }

    try
    {
        d_ast(val(2), '%', val(5)).accept(eval());
        BOOST_ERROR("No exception thrown on float modulo");
    }
    catch (const std::runtime_error & e)
    {
        BOOST_CHECK(strcmp(e.what(), "unknown symbol provided %") == 0);
    }
}


BOOST_AUTO_TEST_CASE(INT_AST)
{
    BOOST_CHECK_EQUAL(2, dual_ast<int>(new value_ast<int>(12), '%', new value_ast<int>(5)).accept(evaluation_ast_visitor<int>()));
}

