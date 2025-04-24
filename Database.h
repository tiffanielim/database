//
// Created by Tiffanie Lim on 12/5/24.
//

#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H
#include "QueryParser.h"
#include "Table.h"
#include "Spreadsheet.h"
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <algorithm>

class Database {
private:
    std::map<std::string, Table> tables;
    std::map<std::string, Spreadsheet> spreadsheets;
//    std::map<std::string, std::vector<std::string>> lastQueryResults;
    bool hasNewResults = false;

    std::vector<std::string> parseColumns(const std::string& columns);
    std::string lastQueryTable;

public:
    void query(const std::string& queryString);

    const std::map<std::string, std::vector<std::string>>& getResults() const;
    bool hasResults() const;

    std::map<std::string, std::vector<std::string>> lastQueryResults;

    void createTable(const std::map<std::string, std::string>& tokens);
    void insertIntoTable(const std::map<std::string, std::string>& tokens);
    void deleteTable(const std::map<std::string, std::string>& tokens);
    void selectFromTable(const std::map<std::string, std::string>& tokens);
    bool evaluateCondition(const std::string& key, const std::string& value, const std::string& condition);

    Table& getTable(const std::string& tableName);
    Spreadsheet& getSpreadsheet(const std::string& tableName);
};

#endif //DATABASE_DATABASE_H
