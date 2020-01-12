//
// Created by pierreantoine on 11/01/2020.
//

#include <stdio.h>
#include <stdarg.h>
#include <src/flex.h>

#include "src/value_ast.h"
#include "src/single_ast.h"
#include "src/dual_ast.h"
#include "src/evaluation_ast_visitor.h"
#include "src/ast_lockguard.h"

typedef v1::ast::fb31::ast<double> ast;
typedef v1::ast::fb31::value_ast<double> val_ast;
typedef v1::ast::fb31::single_ast<double> s_ast;
typedef v1::ast::fb31::dual_ast<double> d_ast;
typedef v1::ast::fb31::evaluation_ast_visitor<double> eval;
typedef v1::ast::fb31::ast_lockguard<double> ast_lockguard;
typedef v1::ast::fb31::ast<double>* astptr;