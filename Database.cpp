//
// Created by Tiffanie Lim on 12/5/24.
//

#include "Database.h"

bool Database::hasResults() const
{
    return hasNewResults;
}

std::vector<std::string> Database::parseColumns(const std::string& columns)
{
    std::vector<std::string> result;
    std::istringstream stream(columns);
    std::string column;

    while (std::getline(stream, column, ','))
    {
        column.erase(std::remove_if(column.begin(), column.end(), ::isspace), column.end());
        result.push_back(column);
    }

    std::cout << "Parsed columns: ";
    for (const auto& col : result)
    {
        std::cout << col << " ";
    }
    std::cout << "\n";

    return result;
}

Table& Database::getTable(const std::string& tableName)
{
    auto it = tables.find(tableName);
    if (it == tables.end())
        throw std::invalid_argument("Table '" + tableName + "' has been deleted! Yay");

    return it->second;
}

void Database::query(const std::string& queryString)
{
    QueryParser parser;
    auto tokens = parser.parse(queryString);

    std::cout << "Parsed tokens:\n";
    for (const auto& [key, value] : tokens)
        std::cout << "  " << key << ": " << value << "\n";

    const std::string& command = tokens["command"];
    std::cout << "Executing command: " << command << "\n";

    if (command == "CREATE") {
        createTable(tokens);
    } else if (command == "INSERT") {
        insertIntoTable(tokens);
    } else if (command == "SELECT") {
        selectFromTable(tokens);
    } else if (command == "DELETE") {
        //debugging for delete
        std::cout << "DELETE query tokens:\n";
        for (const auto& [key, value] : tokens)
            std::cout << key << ": " << value << "\n";

        deleteTable(tokens);
    } else {
        throw std::invalid_argument("Invalid command: " + command);
    }
}

void Database::createTable(const std::map<std::string, std::string>& tokens)
{
    if (tokens.find("table") == tokens.end() || tokens.find("columns") == tokens.end())
        throw std::invalid_argument("CREATE query missing 'table' or 'columns' key.");

    const std::string& tableName = tokens.at("table");
    lastQueryTable = tableName;
    auto columns = parseColumns(tokens.at("columns"));

    if (tables.find(tableName) != tables.end())
        throw std::invalid_argument("Table '" + tableName + "' already exists.");

    tables.emplace(tableName, Table(columns));
    Spreadsheet sheet(0, columns.size());
    for (const auto& column : columns)
    {
        Header header(column);
        sheet.addHeader(header);
    }
    spreadsheets.emplace(tableName, sheet);
}


void Database::insertIntoTable(const std::map<std::string, std::string>& tokens)
{
    const std::string& tableName = tokens.at("table");
    auto columns = parseColumns(tokens.at("columns"));
    auto values = parseColumns(tokens.at("values"));

    if (columns.size() != values.size())
        throw std::invalid_argument("Number of columns and values do not match.");

    Table& table = getTable(tableName);
    Spreadsheet& sheet = spreadsheets.at(tableName);

    for (size_t i = 0; i < columns.size(); ++i)
        table.insert({columns[i], values[i]});

    Row row;
    for (const auto& value : values)
    {
        Cell cell;
        cell.setValue(value);
        row.addCell(cell);
    }
    sheet.addRow(row);
}

void Database::selectFromTable(const std::map<std::string, std::string>& tokens)
{
    if (tokens.find("columns") == tokens.end() || tokens.at("columns").empty())
        throw std::invalid_argument("SELECT query missing 'columns' key.");

    const std::string& tableName = tokens.at("table");
    auto columns = parseColumns(tokens.at("columns"));

    std::cout << "SELECT columns: ";
    for (const auto& col : columns)
        std::cout << col << " ";

    std::cout << "\n";

    Table& table = getTable(tableName);
    Spreadsheet& sheet = spreadsheets.at(tableName);
    sheet.clearHighlights();

    for (const auto& column : columns)
    {
        auto columnIndex = table.getColumnIndex(column);
        sheet.highlightColumn(columnIndex);
    }

    hasNewResults = true;

    for (const auto& column : columns)
    {
        if (!table.hasColumn(column))
            throw std::invalid_argument("Column '" + column + "' does not exist in table '" + tableName + "'.");

        auto columnIndex = table.getColumnIndex(column);
        std::cout << "Highlighting column: " << column << " at index " << columnIndex << "\n"; // Debug output
        if (columnIndex == std::string::npos)
            throw std::invalid_argument("Column '" + column + "' does not exist in table '" + tokens.at("table") + "'.");

        sheet.highlightColumn(columnIndex);
    }
}

void Database::deleteTable(const std::map<std::string, std::string>& tokens)
{
    const std::string& tableName = tokens.at("table");

    auto it = tables.find(tableName);
    if (it == tables.end())
        throw std::invalid_argument("Table '" + tableName + "' does not exist.");

    tables.erase(it);
    spreadsheets.erase(tableName);
}

const std::map<std::string, std::vector<std::string>>& Database::getResults() const
{
    return lastQueryResults;
}

Spreadsheet& Database::getSpreadsheet(const std::string& tableName)
{
    auto it = spreadsheets.find(tableName);
    if (it == spreadsheets.end())
        throw std::invalid_argument("Spreadsheet for table '" + tableName + "' does not exist.");

    return it->second;
}