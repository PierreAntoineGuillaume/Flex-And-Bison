//
// Created by pierreantoine on 08/01/2020.
//

#include "reference.h"

#include <utility>


reference::reference(std::string filename, int line, int flags)
        : filename(std::move(filename)), line(line), flags(flags)
{

}
