//
// Created by pierreantoine on 09/01/2020.
//


#pragma once


#include <unordered_map>
#include "symbol.h"


namespace symbol
{
    class symbol_catalog
    {
    public:
        typedef std::unordered_map<std::string, symbol> symbol_map;
        typedef symbol_map::iterator iterator;
        typedef symbol_map::const_iterator const_iterator;
    private:
        symbol_map catalog;
    public:

        [[nodiscard]] const_iterator cbegin() const;
        [[nodiscard]] const_iterator cend() const;

        iterator begin();
        iterator end();

        symbol & lookup(const std::string & key);

        symbol_catalog() = default;
        symbol_catalog(const symbol_catalog &) = delete;
    };
}
