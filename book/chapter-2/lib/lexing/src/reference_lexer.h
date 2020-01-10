//
// Created by pierreantoine on 09/01/2020.
//


#pragma once


#include "src/symbol_manager.hpp"
#include "src/symbol_catalog.h"
#include "lexer_interface.h"


class reference_lexer : public lexer_interface
{
    symbol_manager<symbol_catalog> manager {};
    std::string current_file;
public:
    reference_lexer();
    void lex() override;
    void lineno() override;
    void match(const std::string & a_string) override;
    ~reference_lexer() = default;
    void lexFile(const std::string & filename, FILE* handle);
    void lexSTDIN();
};