//
// Created by User on 1/19/2026.
//

#include "Table.h"

uint64_t Table::makeKey(int64_t r, int64_t c) {
     return r << 32 | c;
}

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

}

void Table::printExpression(Area area) const {

}

void Table::printValAll() const {

}

void Table::printExpressionAll() const {

}

double Table::sum(Coordinates leftCell, Coordinates rightCell) const {
    return this->cells.at(Table::makeKey(leftCell.row, leftCell.col)).cachedValue
    + this->cells.at(Table::makeKey(rightCell.row, rightCell.col)).cachedValue;
}

double Table::count(Coordinates leftCell, Coordinates rightCell) const {

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