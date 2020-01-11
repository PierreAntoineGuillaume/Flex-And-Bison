//
// Created by pierreantoine on 08/01/2020.
//

#include "symbol.h"

#include <utility>
#include <iostream>


void report(const symbol::reference & a_reference, const std::string & name)
{
    std::cout << "From: " << a_reference << " marked symbol: \033[4m" + name + "\033[0m\n";
}

void symbol::symbol::mark(const reference & a_reference)
{
    this->add(a_reference);
}

void symbol::symbol::add(const reference & new_reference)
{
    for (const auto & ref:catalog)
    {
        if (ref == new_reference)
        {
            return;
        }
    }
    catalog.push_back(new_reference);
}

symbol::symbol::symbol(std::string name)
        : name(std::move(name))
{

}

symbol::symbol::const_iterator symbol::symbol::cbegin() const
{
    return catalog.cbegin();
}

symbol::symbol::const_iterator symbol::symbol::cend() const
{
    return catalog.cend();
}

symbol::symbol::iterator symbol::symbol::begin()
{
    return catalog.begin();
}

symbol::symbol::iterator symbol::symbol::end()
{
    return catalog.end();
}
