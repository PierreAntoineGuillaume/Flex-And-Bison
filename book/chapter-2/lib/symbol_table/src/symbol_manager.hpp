//
// Created by pierreantoine on 09/01/2020.
//


#pragma once


#include <memory>
#include "reference.h"

template <typename T>
concept bool SymbolCollector() {
    return requires (T collector) {
        { collector.lookup("") -> symbol }
    };
}


template <class SymbolCollector>
class symbol_manager
{
    SymbolCollector collection;
public:
    explicit symbol_manager();
    void add(const std::string & name, const std::string & filename, int line, int flags);
};

template <class SymbolCollector>
symbol_manager<SymbolCollector>::symbol_manager()
        : collection(SymbolCollector())
{

}

template <class SymbolCollector>
void symbol_manager<SymbolCollector>::add(const std::string & name, const std::string & filename, int line, int flags)
{
    auto& symbol = collection.lookup(name);
    symbol.mark(reference(filename, line, flags));
}

