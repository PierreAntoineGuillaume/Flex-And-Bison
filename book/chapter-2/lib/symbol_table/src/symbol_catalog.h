//
// Created by pierreantoine on 09/01/2020.
//


#pragma once


#include <unordered_map>
#include "symbol.h"


class symbol_catalog
{
private:
    std::unordered_map<std::string, symbol> catalog;
public:
    symbol & lookup(const std::string & key);
    [[nodiscard]] const std::unordered_map<std::string, symbol>& get_catalog() const;
};

