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
    std::list<reference> catalog;
    void add(const reference & new_reference);
public:
    const std::string name;
    [[nodiscard]] const std::list<reference>& get_catalog() const;
    explicit symbol(std::string string);
    void mark(const reference & a_reference);
};
