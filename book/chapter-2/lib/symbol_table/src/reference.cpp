//
// Created by pierreantoine on 08/01/2020.
//

#include "reference.h"

#include <utility>
#include <iomanip>


reference::reference(std::string filename, int line, int flags)
        : filename(std::move(filename)), line(line), flags(flags)
{

}

std::ostream & operator<<(std::ostream & os, const reference & reference)
{
    return os << reference.filename + ':' + std::to_string(reference.line);
}

bool operator==(const reference & lhs, const reference & rhs)
{
    return lhs.filename == rhs.filename && lhs.line == rhs.line;
}

bool operator!=(const reference & lhs, const reference & rhs)
{
    return !(lhs == rhs);
}