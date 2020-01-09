//
// Created by pierreantoine on 08/01/2020.
//

#include "symbol.h"

#include <utility>
#include <iostream>


void symbol::mark(const reference & a_reference)
{
    std::cout << "marked symbol: «" + this->name + "» from "
        << a_reference.filename + ":"
        << a_reference.line << "\n";
    catalog.add(a_reference);
}

symbol::symbol(std::string string)
        : name(std::move(string))
{

}
