//
// Created by Tiffanie Lim on 11/7/24.
//

#include "Backspace.h"

void Backspace::saveState(const std::string& state)
{
    states.push(state);
}

std::string Backspace::undo()
{
    if (!states.empty())
    {
        std::string lastState = states.top();
        states.pop();
        return lastState;
    }
    return "";
}
