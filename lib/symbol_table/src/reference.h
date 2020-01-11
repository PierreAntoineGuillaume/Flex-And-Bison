//
// Created by pierreantoine on 08/01/2020.
//


#pragma once


#include <string>


namespace symbol
{
    class reference
    {
    public:
        const std::string filename;
        const int line;
        const std::size_t column;
        const int flags;

        reference(std::string filename, int line, std::size_t column, int flags);
    };

    std::ostream & operator<<(std::ostream & os, const reference & reference);

    bool operator==(const reference & lhs, const reference & rhs);
    bool operator!=(const reference & lhs, const reference & rhs);
}
