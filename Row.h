//
// Created by Tiffanie Lim on 12/4/24.
//

#ifndef DATABASE_ROW_H
#define DATABASE_ROW_H
#include <iostream>
#include "Cell.h"
#include <vector>

class Row {
private:
    std::vector<Cell> _cells;

public:
    void addCell(const Cell &cell);

    const std::vector<Cell>& getCells() const;
    std::vector<Cell>& getCells();
    const Cell& getCell(size_t columnIndex) const;
};

#endif //DATABASE_ROW_H
