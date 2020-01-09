//
// Created by pierreantoine on 09/01/2020.
//

#include "basic_lexer.h"

#include <iostream>

#include "flex.h"


void basic_lexer::lex()
{
    yylex();
}
void basic_lexer::lineno()
{
    std::cout << yylineno << "\n";
}
void basic_lexer::match(const std::string & a_string)
{
    std::cout << "matching:" << a_string << "\n";
}

basic_lexer::basic_lexer()
{
    yylineno=1;
}
