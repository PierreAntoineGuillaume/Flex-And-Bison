//
// Created by pierreantoine on 09/01/2020.
//

#include <iostream>
#include "symbol_catalog.h"


symbol & symbol_catalog::lookup(const std::string & key)
{
    auto symbol_link = catalog.find(key);
    if (symbol_link != catalog.end())
    {
        return symbol_link->second;
    }
    auto insertion = catalog.insert({key, symbol(key)});
    if (!insertion.second)
    {
        throw std::runtime_error("insert failed");
    }
    return insertion.first->second;
}

symbol_catalog::const_iterator symbol_catalog::cbegin() const
{
    return catalog.cbegin();
}

symbol_catalog::const_iterator symbol_catalog::cend() const
{
    return catalog.cend();
}

symbol_catalog::iterator symbol_catalog::begin()
{
    return catalog.begin();
}

symbol_catalog::iterator symbol_catalog::end()
{
    return catalog.end();
}
