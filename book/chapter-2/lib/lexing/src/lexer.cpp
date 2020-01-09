//
// Created by pierreantoine on 08/01/2020.
//

#include <iostream>

#include "lexer.h"
#include "flex.h"

void lexer::lex()
{
    yylex();
}
void lexer::lineno()
{
    std::cout << yylineno << "\n";
}
