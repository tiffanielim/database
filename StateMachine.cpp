//
// Created by Tiffanie Lim on 12/4/24.
//

#include "StateMachine.h"

StateMachine::StateMachine(const std::initializer_list<std::pair<std::string, std::set<std::string>>> &list)
{
    for (const auto &item : list)
        transitions[item.first] = item.second;
}

void StateMachine::addState(const std::string &state, const std::set<std::string> &nextStates)
{
    transitions[state] = nextStates;
}

bool StateMachine::validate(const std::vector<std::string> &tokens) const
{
    std::string currentState = "START";
    size_t i = 0;

    while (i < tokens.size())
    {
        const auto &token = tokens[i];
        const auto &neighborsIter = transitions.find(currentState);
        if (neighborsIter == transitions.end())
            return false;

        const auto &neighbors = neighborsIter->second;

        if (neighbors.find(token) != neighbors.end())
        {
            currentState = token;
            ++i;
            continue;
        }

        //wildcard transitions checking
        std::string wildcardState;
        for (const auto &nextState : neighbors)
        {
            if (!nextState.empty() && nextState[0] == '*')
            {
                wildcardState = nextState;
                break;
            }
        }

        if (!wildcardState.empty())
        {
            //transition into wildcard state
            currentState = wildcardState;

            const auto &wildcardNeighborsIter = transitions.find(currentState);
            if (wildcardNeighborsIter != transitions.end())
            {
                const auto &wildcardNeighbors = wildcardNeighborsIter->second;

                //if token is a specific transition OUTTT of the wildcard state
                if (wildcardNeighbors.find(token) != wildcardNeighbors.end())
                {
                    currentState = token;
                    ++i;
                    continue;
                }
            }

            ++i;
            continue;
        }

        if (currentState.size() > 0 && currentState[0] == '*')
        {
            ++i;
            continue;
        }
        return false;
    }
    return true;
}
