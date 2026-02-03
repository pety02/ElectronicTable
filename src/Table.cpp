//
// Created by User on 1/19/2026.
//

#include "Table.h"
#include <iostream>

std::pair<int64_t, int64_t> Table::findTableBounds() const {
    int64_t maxRow = 0;
    int64_t maxCol = 0;

    for (const auto& [key, cell] : cells) {
        maxRow = std::max(maxRow, cell.coords.row);
        maxCol = std::max(maxCol, cell.coords.col);
    }

    return {maxRow, maxCol};
}

Table::Table() : cells(std::unordered_map<Coordinates, Cell, Hash>()), focusedCoords(Coordinates()) {}

void Table::set(Coordinates coords, const std::string &expression) {
  if(coords.row < 0 || coords.col < 0) {
      this->focusedCoords.row += coords.row;
      this->focusedCoords.col += coords.col;
  } else {
      this->focusedCoords.row = coords.row;
      this->focusedCoords.col = coords.col;
  }

  this->cells[this->focusedCoords] = Cell(expression, this->focusedCoords);
}

std::string Table::get(Coordinates coords) const {
  return this->cells.at(coords).expression;
}

double Table::sum(Coordinates leftCell, Coordinates rightCell) const {
    return this->cells.at(leftCell).cachedValue
    + this->cells.at(rightCell).cachedValue;
}

int Table::count(Coordinates leftCell, Coordinates rightCell) const {
    if (rightCell.row < leftCell.row) {
        throw std::invalid_argument("Invalid x coordinates");
    }
    if (rightCell.col < leftCell.col) {
        throw std::invalid_argument("Invalid y coordinates");
    }

    int counter = 0;
    for(int64_t i = leftCell.row; i < rightCell.row; ++i) {
        for (int64_t j = leftCell.col; j < rightCell.col; ++j) {
            Coordinates currentCell = {i, j};
            if(!this->cells.at(currentCell).expression.empty()) {
                counter++;
            }
        }
    }

    return counter;
}

double Table::min(Coordinates leftCell, Coordinates rightCell) const {
    const double left = this->cells.at(leftCell).cachedValue;
    const double right = this->cells.at(rightCell).cachedValue;

    if (left < right)
        return left;

    return right;
}

double Table::max(Coordinates leftCell, Coordinates rightCell) const {
    const double left = this->cells.at(leftCell).cachedValue;
    const double right = this->cells.at(rightCell).cachedValue;

    if (left > right)
        return left;

    return right;
}

double Table::avg(Coordinates leftCell, Coordinates rightCell) const {
    const double left = this->cells.at(leftCell).cachedValue;
    const double right = this->cells.at(rightCell).cachedValue;

    return (left + right) / 2;
}

const std::unordered_map<Coordinates, Cell, Hash>& Table::getCells() const {
    return this->cells;
}

double Table::getCachedValue(const Coordinates &address) const {
    return this->cells.at(address).cachedValue;
}

void Table::setCachedValue(double value, const Coordinates &address) {
    this->cells.at(address).cachedValue = value;
}