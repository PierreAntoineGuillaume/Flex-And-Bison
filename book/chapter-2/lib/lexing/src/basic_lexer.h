//
// Created by pierreantoine on 09/01/2020.
//


#pragma once


#include "lexer_interface.h"


class basic_lexer : public lexer_interface
{
public:
    basic_lexer();
    void lex() override;
    void lineno() override;
    void match(const std::string & a_string) override;
    ~basic_lexer() = default;
};