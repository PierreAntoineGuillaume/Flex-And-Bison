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
    manager.add(a_string, this->current_file, yylineno, 0);
}

reference_lexer::reference_lexer()
{
    yylineno = 1;
}
void reference_lexer::lexFile(const std::string & filename, FILE *handle)
{
    this->current_file = filename;
    yyrestart(handle);
    this->lex();
}
void reference_lexer::lexSTDIN()
{
    lexFile("(stdin)", stdin);
}
