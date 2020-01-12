//
// Created by pierreantoine on 12/01/2020.
//


#include <memory>
#include <boost/test/unit_test.hpp>
#include "src/value_ast.h"

#include "src/single_ast.h"
#include "src/evaluation_ast_visitor.h"


using namespace v1::ast::fb31;

typedef value_ast<int> val_ast;
typedef single_ast<int> s_ast;
typedef dual_ast<int> d_ast;
typedef evaluation_ast_visitor<int> eval;

BOOST_AUTO_TEST_CASE(INT_AST)
{
    auto five  = std::make_shared<val_ast>(5);
    auto mfive = std::make_shared<val_ast>(-5);
    auto zero  = std::make_shared<val_ast>(0);

    auto evaler = eval();
    BOOST_CHECK_EQUAL(5, five->accept(evaler));
    BOOST_CHECK_EQUAL(-5, mfive->accept(evaler));
    BOOST_CHECK_EQUAL(-5, s_ast('M', five).accept(evaler));
    BOOST_CHECK_EQUAL(5, s_ast('M', mfive).accept(evaler));
    BOOST_CHECK_EQUAL(10, d_ast('-', five, mfive).accept(evaler));

    try
    {
        d_ast('/', five, zero).accept(evaler);
        BOOST_ERROR("No exception thrown on zero division");
    }
    catch (const std::runtime_error & e)
    {
        BOOST_CHECK(strcmp(e.what(), "zero division") == 0);
    }

}