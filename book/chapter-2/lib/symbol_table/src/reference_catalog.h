//
// Created by pierreantoine on 08/01/2020.
//


#pragma once


#include <list>
#include "reference.h"


class reference_catalog
{
private:
    std::list<reference> collection;
public:
    void add(const reference& reference);
};

