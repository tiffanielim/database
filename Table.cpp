//
// Created by Tiffanie Lim on 12/5/24.
//

#include "Table.h"

Table::Table(const std::vector<std::string>& columns)
        : columns(columns) {}

void Table::insert(const std::pair<std::string, std::string>& entry)
{
    const std::string& column = entry.first;
    const std::string& value = entry.second;

    if (!hasColumn(column))
        throw std::invalid_argument("Invalid column name: " + column);

    data.insert(entry);
}

bool Table::hasColumn(const std::string& column) const
{
    return std::find(columns.begin(), columns.end(), column) != columns.end();
}

void Table::printData() const
{
    for (const auto& [key, value] : data)
        std::cout << key << ": " << value << "\n";
}

size_t Table::getColumnIndex(const std::string& column) const
{
    auto it = std::find(columns.begin(), columns.end(), column);
    if (it == columns.end())
        throw std::invalid_argument("Column '" + column + "' does not exist.");

    size_t index = std::distance(columns.begin(), it);
    std::cout << "Column '" << column << "' is at index " << index << "\n";
    return index;
}

std::vector<std::string> Table::getColumns() const {
    return columns;
}

std::vector<std::unordered_map<std::string, std::string>> Table::getData() const {
    std::vector<std::unordered_map<std::string, std::string>> rows;

    for (const auto& entry : data) {
        std::unordered_map<std::string, std::string> row;
        row[entry.first] = entry.second;
        rows.push_back(row);
    }
    return rows;
}
