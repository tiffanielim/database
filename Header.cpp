//
// Created by Tiffanie Lim on 12/4/24.
//

#include "Header.h"

Header::Header(const std::string &name)
        : _name(name)
{}

std::string Header::getName() const
{
    return _name;
}

void Header::setName(const std::string &name)
{
    _name = name;
}