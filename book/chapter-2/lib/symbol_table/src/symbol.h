//
// Created by pierreantoine on 08/01/2020.
//

#pragma once


#include <string>
#include <list>
#include "reference.h"


class symbol
{
private:
    const std::string name;
    std::list<reference> catalog;
    void add(const reference & new_reference);
public:
    explicit symbol(std::string string);
    symbol (const symbol&) = default;
    ~symbol() = default;
    void mark(const reference & a_reference);
};
