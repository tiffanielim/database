//
// Created by Tiffanie Lim on 12/5/24.
//

#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>

class Table {
private:
    std::vector<std::string> columns;
    std::multimap<std::string, std::string> data;
    friend class Database;

public:
    Table(const std::vector<std::string>& columns);

    void insert(const std::pair<std::string, std::string>& entry);
    bool hasColumn(const std::string& column) const;
    void printData() const;
    std::vector<std::string> getColumns() const;
    std::vector<std::unordered_map<std::string, std::string>> getData() const;
    size_t getColumnIndex(const std::string& column) const;

};

#endif //DATABASE_TABLE_H
