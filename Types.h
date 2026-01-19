//
// Created by User on 1/19/2026.
//

#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <string>

struct Coordinates {
  int64_t row;
  int64_t col;
};

struct Area {
    Coordinates from;
    Coordinates to;
};

struct Cell {
    std::string expression;
    bool cacheable = false;
    double cachedValue = 0.0;
    Coordinates coords;
};

enum TokenType {
    Number,
    Identifier,
    Operator,
    LParen, RParen,
    Comma,
    End
};

struct Token {
    TokenType type;
    std::string text;
};

#endif //TYPES_H