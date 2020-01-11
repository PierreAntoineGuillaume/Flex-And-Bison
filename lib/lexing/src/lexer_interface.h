//
// Created by pierreantoine on 08/01/2020.
//


#pragma once


#include <string>

class lexer_interface
{
public:
    virtual void lex() = 0;
    virtual void lineno() = 0;
    virtual void match(const std::string & a_string) =0;
    ~lexer_interface() = default;
};

