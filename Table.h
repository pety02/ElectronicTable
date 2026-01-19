//
// Created by User on 1/19/2026.
//

#ifndef TABLE_H
#define TABLE_H

#include "Types.h"
#include <unordered_map>

class Table {
private:
  std::unordered_map<uint64_t, Cell> cells;

  uint64_t makeKey(int64_t r, int64_t c) const;

public:
  void set(Coordinates coords, std::string expression);
  void printVal(Area area) const;
  void printExpression(Area area) const;
  void printValAll() const;
  void printExpressionAll() const;

  double sum(Coordinates leftCell, Coordinates rightCell) const;
  double count(Coordinates leftCell, Coordinates rightCell) const;
  double min(Coordinates leftCell, Coordinates rightCell) const;
  double max(Coordinates leftCell, Coordinates rightCell) const;
  double avg(Coordinates leftCell, Coordinates rightCell) const;
};

#endif //TABLE_H