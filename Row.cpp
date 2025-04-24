//
// Created by Tiffanie Lim on 12/4/24.
//

#include "Row.h"

void Row::addCell(const Cell& cell)
{
    _cells.push_back(cell);
}

const std::vector<Cell>& Row::getCells() const
{
    return _cells;
}

std::vector<Cell>& Row::getCells()
{
    return _cells;
}

const Cell& Row::getCell(size_t columnIndex) const
{
    if (columnIndex >= _cells.size())
        throw std::out_of_range("Invalid column index.");

    return _cells[columnIndex];
}