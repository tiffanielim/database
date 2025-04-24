//
// Created by Tiffanie Lim on 11/26/24.
//
#include "Spreadsheet.h"
Spreadsheet::Spreadsheet(int rows, int columns)
        : _rows(rows), _columns(columns)
{
    initializeGrid();
}

Spreadsheet::Spreadsheet(const std::vector<std::vector<std::string>> &data)
{
    _rows = data.size();
    _columns = data[0].size();

    initializeGrid();

    for (int i = 0; i < _rows; i++)
        for (int j = 0; j <_columns; j++)
            setCellText(i, j, data[i][j]);

}

void Spreadsheet::initializeGrid()
{
    _grid.resize(_rows, std::vector<Cell>(_columns));

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            float x = j * _cellWidth;
            float y = i * _cellHeight;
            _grid[i][j].setSize(_cellWidth, _cellHeight);
            _grid[i][j].setPosition(x, y);
        }
    }
}

void Spreadsheet::setCellText(int row, int column, const std::string &text)
{
    _grid[row][column].setText(text);
}

void Spreadsheet::draw(sf::RenderTarget &target)
{
    //for headers
    for (size_t col = 0; col < _headers.size(); ++col)
    {
        Cell headerCell;
        headerCell.setSize(_cellWidth, _cellHeight);
        headerCell.setPosition(_offset.x + col * _cellWidth, _offset.y);
        headerCell.setValue(_headers[col].getName());

        if (std::find(_highlightedColumns.begin(), _highlightedColumns.end(), col) != _highlightedColumns.end())
        {
            headerCell.setOutlineColor(sf::Color::Blue);
            headerCell.setOutlineThickness(2.f);
            headerCell.setFillColor(sf::Color(200, 200, 255));
//            headerCell.setFillColor(sf::Color(255, 255, 194));
        } else {
            headerCell.setOutlineColor(sf::Color::Black);
            headerCell.setOutlineThickness(1.f);
        }
        headerCell.draw(target);
    }

    //for rows
    for (size_t row = 0; row < _rowsData.size(); ++row)
    {
        const Row &currentRow = _rowsData[row];
        const auto &cells = currentRow.getCells();

        for (size_t col = 0; col < cells.size(); ++col)
        {
            Cell cell = cells[col];
            cell.setSize(_cellWidth, _cellHeight);
            cell.setPosition(_offset.x + col * _cellWidth, _offset.y + (row + 1) * _cellHeight);

            if (std::find(_highlightedColumns.begin(), _highlightedColumns.end(), col) != _highlightedColumns.end())
            {
                cell.setOutlineColor(sf::Color::Blue);
                cell.setOutlineThickness(2.f);
                cell.setFillColor(sf::Color(200, 200, 255));
            } else {
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(1.f);
            }
            cell.draw(target);
        }
    }
}


void Spreadsheet::addHeader(const Header &header)
{
    _headers.push_back(header);
}

void Spreadsheet::addRow(const Row &row)
{
    _rowsData.push_back(row);
}

Row &Spreadsheet::getRow(size_t index)
{
    return _rowsData.at(index);
}

size_t Spreadsheet::getColumnCount() const
{
    return _headers.size();
}

void Spreadsheet::loadFromVector(const std::vector<std::vector<std::string>> &data)
{
    if (data.empty())
        return;

    _headers.clear();
    for (const auto &headerName : data[0])
    {
        Header header(headerName);
        addHeader(header);
    }

    _rowsData.clear();
    for (size_t i = 1; i < data.size(); ++i)
    {
        Row row;
        for (const auto &cellValue : data[i])
        {
            Cell cell;
            cell.setValue(cellValue);
            row.addCell(cell);
        }
        addRow(row);
    }
}

void Spreadsheet::setOffset(float x, float y)
{
    _offset = {x, y};
}

void Spreadsheet::highlightRow(size_t rowIndex)
{
    _highlightedRows.push_back(rowIndex);
}

void Spreadsheet::highlightColumn(size_t colIndex)
{
    if (colIndex >= _columns)
        throw std::out_of_range("Column index out of range for highlighting.");

    _highlightedColumns.push_back(colIndex);

    for (size_t row = 0; row < _rows; ++row)
    {
        _grid[row][colIndex].setOutlineColor(sf::Color::Blue);
        _grid[row][colIndex].setOutlineThickness(2.f);
    }
}

void Spreadsheet::clearHighlights()
{
    _highlightedRows.clear();
    _highlightedColumns.clear();
}

size_t Spreadsheet::getRowCount() const
{
    return _rowsData.size();
}

std::string Spreadsheet::getHeaderName(size_t colIndex) const
{
    if (colIndex >= _headers.size())
        throw std::out_of_range("Column index out of range");

    return _headers[colIndex].getName();
}
