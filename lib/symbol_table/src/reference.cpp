//
// Created by pierreantoine on 08/01/2020.
//

#include "reference.h"

#include <utility>
#include <iomanip>


symbol::reference::reference(std::string filename, int line, std::size_t column, int flags)
        : filename(std::move(filename)), line(line), column(column), flags(flags)
{

}

std::ostream & symbol::operator<<(std::ostream & os, const reference & reference)
{
    return os << reference.filename + ':' + std::to_string(reference.line) + ':' + std::to_string(reference.column);
}

bool symbol::operator==(const reference & lhs, const reference & rhs)
{
    return lhs.filename == rhs.filename && lhs.line == rhs.line && lhs.column == rhs.column;
}

bool symbol::operator!=(const reference & lhs, const reference & rhs)
{
    return !(lhs == rhs);
}