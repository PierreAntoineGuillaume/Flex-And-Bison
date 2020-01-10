//
// Created by pierreantoine on 08/01/2020.
//

#include "symbol.h"

#include <utility>
#include <iostream>


void report(const reference & a_reference, const std::string & name)
{
    std::cout << "From: " << a_reference << " marked symbol: \033[4m" + name + "\033[0m\n";
}

void symbol::mark(const reference & a_reference)
{
    report(a_reference, name);
    catalog.add(a_reference);
}

symbol::symbol(std::string string)
        : name(std::move(string))
{

}
