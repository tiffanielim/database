//
// Created by Tiffanie Lim on 12/4/24.
//

//tokenizer splits a given string into a vector
//query parser: brings it together 1. tokenizer 2. gives to state machine and formats the way it wants

#ifndef DATABASE_QUERYPARSER_H
#define DATABASE_QUERYPARSER_H
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <map>
#include "StateMachine.h"

class QueryParser {
private:
    StateMachine stateMachine;
    std::vector<std::string> tokenize(const std::string &query);

public:
    QueryParser();
    std::map<std::string, std::string> parse(const std::string &query);
};

#endif //DATABASE_QUERYPARSER_H
