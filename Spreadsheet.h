//
// Created by Tiffanie Lim on 11/26/24.
//

#ifndef CS8_DATABASE_SPREADSHEET_H
#define CS8_DATABASE_SPREADSHEET_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Font.h"
#include "Cell.h"
#include "Header.h"
#include "Row.h"

class Spreadsheet {
private:
    int _rows;
    int _columns;
    int _cellWidth = 200;
    float _cellHeight = 60;
    sf::Vector2f _offset{0, 0};
    std::vector<std::vector<Cell>> _grid;
    std::vector<Header> _headers;
    std::vector<Row> _rowsData;

    std::vector<size_t> _highlightedRows;
    std::vector<size_t> _highlightedColumns;

    void initializeGrid();

public:
    Spreadsheet(int rows, int columns);
    Spreadsheet(const std::vector<std::vector<std::string>> &data);

    void addHeader(const Header &header);
    void addRow(const Row &row);
    Row &getRow(size_t index);
    size_t getRowCount() const;
    size_t getColumnCount() const;
    std::string getHeaderName(size_t colIndex) const;

    void setCellText(int row, int column, const std::string &text);
    void draw(sf::RenderTarget &target);

    void loadFromVector(const std::vector<std::vector<std::string>> &data);
    void setOffset(float x, float y);
    void highlightRow(size_t rowIndex);
    void highlightColumn(size_t colIndex);
    void clearHighlights();

};

#endif //CS8_DATABASE_SPREADSHEET_H