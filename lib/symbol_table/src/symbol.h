//
// Created by pierreantoine on 08/01/2020.
//

#pragma once


#include <string>
#include <list>
#include "reference.h"

namespace symbol
{

    class symbol
    {
    public:
        typedef std::list<reference> reflist;
        typedef std::list<reference>::iterator iterator;
        typedef std::list<reference>::const_iterator const_iterator;
    private:
        reflist catalog;
        void add(const reference & new_reference);
    public:
        const std::string name;

        [[nodiscard]] const_iterator cbegin() const;
        [[nodiscard]] const_iterator cend() const;

        [[nodiscard]] iterator begin();
        [[nodiscard]] iterator end();

        explicit symbol(std::string string);
        void mark(const reference & a_reference);
    };
}
