//
// Created by User on 1/19/2026.
//

#include "Table.h"
#include <iostream>

uint64_t Table::makeKey(int64_t r, int64_t c) {
     return r << 32 | c;
}

std::pair<int64_t, int64_t> Table::findTableBounds() const {
    int64_t maxRow = 0;
    int64_t maxCol = 0;

    for (const auto& [key, cell] : cells) {
        maxRow = std::max(maxRow, cell.coords.row);
        maxCol = std::max(maxCol, cell.coords.col);
    }

    return {maxRow, maxCol};
}

Table::Table() : cells(std::unordered_map<uint64_t, Cell>()), focusedCoords(Coordinates()) {}

void Table::set(Coordinates coords, const std::string &expression) {
  if(coords.row < 0 || coords.col < 0) {
      this->focusedCoords.row += coords.row;
      this->focusedCoords.col += coords.col;
  } else {
      this->focusedCoords.row = coords.row;
      this->focusedCoords.col = coords.col;
  }

  this->cells[Table::makeKey(this->focusedCoords.row, this->focusedCoords.col)] = Cell(expression, this->focusedCoords);
}

std::string Table::get(Coordinates coords) const {
  return this->cells.at(Table::makeKey(coords.row, coords.col)).expression;
}

void Table::printVal(Area area) const {
    int64_t maxRow = area.maxRow();
    int64_t maxCol = area.maxCol();

    for (int64_t r = 0; r <= maxRow; ++r) {
        for (int64_t c = 0; c <= maxCol; ++c) {
            uint64_t key = makeKey(r, c);
            auto it = cells.find(key);

            if (it != cells.end()) {
                std::cout << it->second.cachedValue;
            }

            if (c != maxCol) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
}

void Table::printExpression(Area area) const {
    int64_t maxRow = area.maxRow();
    int64_t maxCol = area.maxCol();

    for (int64_t r = 0; r <= maxRow; ++r) {
        for (int64_t c = 0; c <= maxCol; ++c) {
            uint64_t key = makeKey(r, c);
            auto it = cells.find(key);

            if (it != cells.end()) {
                std::cout << it->second.expression;
            }

            if (c != maxCol) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
}

void Table::printValAll() const {
    if (cells.empty()) {
        return;
    }

    // Find table bounds
    std::pair<int64_t, int64_t> bounds = this->findTableBounds();
    int maxRow = bounds.first;
    int maxCol = bounds.second;

    // Print row by row
    for (int64_t r = 0; r <= maxRow; ++r) {
        for (int64_t c = 0; c <= maxCol; ++c) {
            uint64_t key = makeKey(r, c);
            auto it = cells.find(key);

            if (it != cells.end()) {
                std::cout << it->second.cachedValue;
            }

            if (c != maxCol) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
}

void Table::printExpressionAll() const {
    if (cells.empty()) {
        return;
    }

    // Find table bounds
    std::pair<int64_t, int64_t> bounds = this->findTableBounds();
    int maxRow = bounds.first;
    int maxCol = bounds.second;

    // Print row by row
    for (int64_t r = 0; r <= maxRow; ++r) {
        for (int64_t c = 0; c <= maxCol; ++c) {
            uint64_t key = makeKey(r, c);
            auto it = cells.find(key);

            if (it != cells.end()) {
                std::cout << it->second.expression;
            }

            if (c != maxCol) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
}

double Table::sum(Coordinates leftCell, Coordinates rightCell) const {
    return this->cells.at(Table::makeKey(leftCell.row, leftCell.col)).cachedValue
    + this->cells.at(Table::makeKey(rightCell.row, rightCell.col)).cachedValue;
}

int Table::count(Coordinates leftCell, Coordinates rightCell) const {
    if (rightCell.row < leftCell.row) {
        throw std::invalid_argument("Invalid x coordinates");
    }
    if (rightCell.col < leftCell.col) {
        throw std::invalid_argument("Invalid y coordinates");
    }

    int counter = 0;
    for(int i = leftCell.row; i < rightCell.row; ++i) {
        for (int j = leftCell.col; j < rightCell.col; ++j) {
            if(!this->cells.at(Table::makeKey(i, j)).expression.empty()) {
                counter++;
            }
        }
    }

    return counter;
}

double Table::min(Coordinates leftCell, Coordinates rightCell) const {
    const double left = this->cells.at(Table::makeKey(leftCell.row, leftCell.col)).cachedValue;
    const double right = this->cells.at(Table::makeKey(rightCell.row, rightCell.col)).cachedValue;

    if (left < right)
        return left;

    return right;
}

double Table::max(Coordinates leftCell, Coordinates rightCell) const {
    const double left = this->cells.at(Table::makeKey(leftCell.row, leftCell.col)).cachedValue;
    const double right = this->cells.at(Table::makeKey(rightCell.row, rightCell.col)).cachedValue;

    if (left > right)
        return left;

    return right;
}

double Table::avg(Coordinates leftCell, Coordinates rightCell) const {
    const double left = this->cells.at(Table::makeKey(leftCell.row, leftCell.col)).cachedValue;
    const double right = this->cells.at(Table::makeKey(rightCell.row, rightCell.col)).cachedValue;

    return (left + right) / 2;
}

const std::unordered_map<uint64_t, Cell> Table::getCells() const {
    return this->cells;
}