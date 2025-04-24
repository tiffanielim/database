//
// Created by Tiffanie Lim on 11/7/24.
//

#ifndef AUTOCORRECT_BACKSPACE_H
#define AUTOCORRECT_BACKSPACE_H
#include <stack>
#include <string>

class Backspace {
private:
    std::stack<std::string> states;

public:
    void saveState(const std::string& state);
    std::string undo();
};

#endif //AUTOCORRECT_BACKSPACE_H
