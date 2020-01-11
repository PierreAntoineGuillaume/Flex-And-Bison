//
// Created by pierreantoine on 09/01/2020.
//


#pragma once


#include <memory>
#include "reference.h"
#include "symbol_catalog.h"

namespace symbol
{
    template <class symbol_collection>
    class symbol_manager
    {
        symbol_collection collection;
    public:
        typedef typename symbol_collection::iterator iterator;
        typedef typename symbol_collection::const_iterator const_iterator;

        iterator begin();
        const_iterator cbegin() const;

        iterator end();
        const_iterator cend() const;

        void add(const std::string & name, const std::string & filename, int line, std::size_t column, int flags);
    };
}

template <class symbol_collection>
void symbol::symbol_manager<symbol_collection>::add(const std::string & name, const std::string & filename, int line, std::size_t column, int flags)
{
    auto & symbol = collection.lookup(name);
    symbol.mark(reference(filename, line, column, flags));
}

template <class symbol_collection>
typename symbol::symbol_manager<symbol_collection>::const_iterator symbol::symbol_manager<symbol_collection>::cbegin() const
{
    return collection.cbegin();
}

template <class symbol_collection>
typename symbol::symbol_manager<symbol_collection>::const_iterator symbol::symbol_manager<symbol_collection>::cend() const
{
    return collection.cend();
}

template <class symbol_collection>
typename symbol::symbol_manager<symbol_collection>::iterator symbol::symbol_manager<symbol_collection>::begin()
{
    return collection.begin();
}

template <class symbol_collection>
typename symbol::symbol_manager<symbol_collection>::iterator symbol::symbol_manager<symbol_collection>::end()
{
    return collection.end();
}
