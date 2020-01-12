//
// Created by pierreantoine on 12/01/2020.
//


#include <memory>
#include <boost/test/unit_test.hpp>
#include "src/value_ast.h"

#include "src/single_ast.h"
#include "src/evaluation_ast_visitor.h"


using namespace v1::ast::fb31;

typedef value_ast<double> val_ast;
typedef single_ast<double> s_ast;
typedef dual_ast<double> d_ast;
typedef evaluation_ast_visitor<double> eval;

inline std::shared_ptr<val_ast> val(double d)
{
    return std::make_shared<val_ast>(d);
}

BOOST_AUTO_TEST_CASE(INT_AST)
{
    BOOST_CHECK_EQUAL(5, val(5)->accept(eval()));
    BOOST_CHECK_EQUAL(-5, val(-5)->accept(eval()));
    BOOST_CHECK_EQUAL(-5, s_ast('M', val(5.f)).accept(eval()));
    BOOST_CHECK_EQUAL(5, s_ast('M', val(-5.f)).accept(eval()));
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

}