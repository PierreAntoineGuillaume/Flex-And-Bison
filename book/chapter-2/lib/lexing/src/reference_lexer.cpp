//
// Created by pierreantoine on 09/01/2020.
//

#include <iostream>

#include "reference_lexer.h"

#include "flex.h"


void reference_lexer::lex()
{
    yylex();
}

void reference_lexer::lineno()
{
    std::cout << yylineno << "\n";
}
void reference_lexer::match(const std::string & a_string)
{
    std::cout << "matching:" << a_string << "\n";
    manager.add(a_string, "", yylineno, 0);
}

reference_lexer::reference_lexer()
{
    yylineno = 1;
}
