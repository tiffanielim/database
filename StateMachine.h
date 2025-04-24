//
// Created by Tiffanie Lim on 12/4/24.
//

#ifndef DATABASE_STATEMACHINE_H
#define DATABASE_STATEMACHINE_H
#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

class StateMachine {
private:
    std::map<std::string, std::set<std::string>> transitions;

public:
    StateMachine() = default;
    StateMachine(const std::initializer_list<std::pair<std::string, std::set<std::string>>> &list);

    void addState(const std::string &state, const std::set<std::string> &nextStates);
    bool validate(const std::vector<std::string> &tokens) const;
};

#endif //DATABASE_STATEMACHINE_H
