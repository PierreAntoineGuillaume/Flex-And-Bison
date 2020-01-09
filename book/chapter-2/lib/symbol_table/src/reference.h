//
// Created by pierreantoine on 08/01/2020.
//


#pragma once


#include <string>


class reference
{
public:
    const std::string filename;
    const int line;
    const int flags;

    reference(std::string filename, int line, int flags);
};

