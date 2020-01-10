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
    manager.add(a_string, this->current_file, yylineno, column, 0);
    skip(a_string);
}

void reference_lexer::lexFile(const std::string & filename, FILE *handle)
{
    this->current_file = filename;

    yylineno = 1;
    resetColumn();
    yyrestart(handle);
    this->lex();
}
void reference_lexer::lexSTDIN()
{
    lexFile("(stdin)", stdin);
}

void reference_lexer::display_table()
{
    for (auto & pair : this->manager)
    {
        std::cout << "References: " << pair.first << ": ";
        for (const auto & ref:pair.second)
        {
            std::cout << ref << ", ";
        }
        std::cout << "\n";
    }
}
void reference_lexer::resetColumn()
{
    column = 1;
}


std::size_t compute_length(const std::string & s)
{
    return (s.length() - count_if(
            s.begin(), s.end(), [](unsigned char c) -> bool
            {
                return (c & 0xC0u) == 0x80;
            }
    ));
}

void reference_lexer::skip(const std::string & ignored)
{
    column += compute_length(ignored);
}