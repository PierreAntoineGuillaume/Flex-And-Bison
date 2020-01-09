//
// Created by pierreantoine on 08/01/2020.
//

#pragma once


#include <string>

#include "reference_catalog.h"
#include "reference.h"

class symbol
{
private:
    std::string name;
    reference_catalog catalog;
public:
    explicit symbol(std::string string);
    void mark(const reference & a_reference);
};
