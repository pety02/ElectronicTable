//
// Created by User on 1/19/2026.
//

#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <string>

/**
 *
 */
struct Coordinates {
    int64_t row;
    int64_t col;

    /**
     *
     * @param row
     * @param col
     */
    Coordinates(int64_t row = 0, int64_t col = 0) : row(row), col(col) {
    }
};

/**
 *
 */
struct Area {
    Coordinates from;
    Coordinates to;

    /**
     *
     * @param from
     * @param to
     */
    Area(Coordinates from, Coordinates to = Coordinates()) : from(from), to(to) {
    }

    /**
     * 
     * @return 
     */
    int64_t maxRow() const {
        return std::max(from.row, to.row);
    }

    /**
     * 
     * @return 
     */
    int64_t maxCol() const {
        return std::max(from.col, to.col);
    }
};

/**
 *
 */
struct Cell {
    std::string expression;
    double cachedValue;
    Coordinates coords;

    /**
     * 
     * @param expression 
     * @param coords 
     */
    Cell(const std::string &expression, const Coordinates coords) : expression(expression),
                                                                    cachedValue(0), coords(coords) {
    }
};

/**
 *
 */
enum TokenType {
    End,
    Number,
    Plus, Minus, Mul, Div, Mod,
    LParen, RParen,
    Comma,
    Equal, NotEqual, Less, Greater,
    Identifier, // functions: sum, if, etc.
    CellRef // RxCy with absolute / relative parts
};

/**
 *
 */
struct Token {
    TokenType type;
    std::string lexeme;

    /**
     *
     * @param type
     * @param lexeme
     */
    Token(const TokenType type, const std::string &lexeme) : type(type), lexeme(lexeme) {
    }
};

#endif //TYPES_H
