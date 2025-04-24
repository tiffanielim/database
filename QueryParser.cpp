//
// Created by Tiffanie Lim on 12/4/24.
//

#include "QueryParser.h"

QueryParser::QueryParser() {
    stateMachine = StateMachine({
        {"START", {"SELECT", "DELETE", "INSERT", "CREATE"}},
        {"SELECT", {"*COLUMNS"}},
        {"*COLUMNS", {"FROM"}},
        {"FROM", {"*TABLE"}},
        {"*TABLE", {"WHERE", "END"}},
        {"WHERE", {"*CONDITION"}},
        {"*CONDITION", {"*CONDITION", "END"}},
        {"INSERT", {"INTO"}},
        {"INTO", {"*TABLE"}},
        {"*TABLE", {"VALUES"}},
        {"VALUES", {"*VALUES"}},
        {"*VALUES", {"*VALUES", "END"}},
        {"CREATE", {"TABLE"}},
        {"TABLE", {"*CREATE_COLUMNS"}},
        {"*CREATE_COLUMNS", {"*CREATE_COLUMNS", "END"}},
        {"DELETE", {"TABLE"}},
        {"TABLE", {"*TABLE"}},
        {"*TABLE", {"END"}}
    });
}

std::vector<std::string> QueryParser::tokenize(const std::string &query)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(query);

    while (stream >> token)
    {
        if (token.back() == ',')
        {
            tokens.push_back(token.substr(0, token.size() - 1));
            tokens.push_back(",");
        } else {
            tokens.push_back(token);
        }
    }

    return tokens;
}

std::map<std::string, std::string> QueryParser::parse(const std::string &query)
{
    std::vector<std::string> tokens = tokenize(query);

    if (!stateMachine.validate(tokens))
        throw std::invalid_argument("SQL query is INVALID buddy!");

    std::map<std::string, std::string> parsedQuery;
    std::string currentSection;
    std::string tempColumns;

    for (const auto &token : tokens)
    {
        if (token == "CREATE" || token == "INSERT" || token == "SELECT" || token == "DELETE")
        {
            parsedQuery["command"] = token;
            currentSection = "command";
        } else if (token == "TABLE" && parsedQuery["command"] == "CREATE") {
            currentSection = "table";  // CREATE TABLE
        } else if (token == "TABLE" && parsedQuery["command"] == "DELETE") {
            currentSection = "table";  // DELETE TABLE
        } else if (token == "INTO" && parsedQuery["command"] == "INSERT") {
            currentSection = "table";  // INSERT INTO
        } else if (token == "VALUES" && parsedQuery["command"] == "INSERT") {
            currentSection = "values";  // INSERT VALUES
        } else if (token == "FROM" && parsedQuery["command"] == "SELECT") {
            currentSection = "table";  // SELECT FROM
        } else if (currentSection == "command" && parsedQuery["command"] == "SELECT") {
            tempColumns += token + " ";
        } else if (currentSection == "table" && parsedQuery["command"] == "SELECT") {
            parsedQuery["table"] = token;
            currentSection.clear();
        } else if (currentSection == "table" && parsedQuery["command"] == "INSERT") {
            parsedQuery["table"] = token;
            currentSection = "columns";
        } else if (currentSection == "table" && parsedQuery["command"] == "CREATE") {
            parsedQuery["table"] = token;
            currentSection = "columns";
        } else if (currentSection == "table" && parsedQuery["command"] == "DELETE") {
            parsedQuery["table"] = token;
            currentSection.clear();
        } else if (currentSection == "columns") {
            tempColumns += token + " ";
        } else if (currentSection == "values") {
            parsedQuery["values"] += (parsedQuery["values"].empty() ? "" : " ") + token;
        } else if (currentSection == "table" && token == "WHERE") {
            currentSection = "where";
        } else if (currentSection == "where") {
            parsedQuery["condition"] += (parsedQuery["condition"].empty() ? "" : " ") + token;
        }
    }

    if (!tempColumns.empty() && parsedQuery["command"] == "SELECT")
    {
        tempColumns = tempColumns.substr(0, tempColumns.find_last_not_of(" ") + 1);
        parsedQuery["columns"] = tempColumns;
    } else if (!tempColumns.empty()) {
        size_t openParen = tempColumns.find('(');
        size_t closeParen = tempColumns.rfind(')');
        if (openParen != std::string::npos && closeParen != std::string::npos)
        {
            parsedQuery["columns"] = tempColumns.substr(openParen + 1, closeParen - openParen - 1);
        } else {
            parsedQuery["columns"] = tempColumns;
        }
    }

    if (parsedQuery["command"] == "INSERT" && !parsedQuery["values"].empty())
    {
        std::string &values = parsedQuery["values"];
        size_t openParen = values.find('(');
        size_t closeParen = values.rfind(')');

        if (openParen != std::string::npos && closeParen != std::string::npos)
            parsedQuery["values"] = values.substr(openParen + 1, closeParen - openParen - 1);
    }

    if (parsedQuery["command"] == "DELETE" && parsedQuery.find("table") == parsedQuery.end())
        throw std::invalid_argument("DELETE query missing table name.");


    for (const auto &[key, value] : parsedQuery)
        std::cout << "key: " << key << ", value: " << value << "\n";

    return parsedQuery;
}

