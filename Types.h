//
// Created by User on 1/19/2026.
//

#ifndef TYPES_H
#define TYPES_H

#include <chrono>
#include <cstdint>
#include <string>

/**
 * Represents the coordinates of the tables' cells as containing the
 * positions of a cell by the axis (row) and ordinate (col).
 */
struct Coordinates {
    int64_t row;
    int64_t col;

    /**
   * Constructs a Coordinates object.
   *
   * The constructor uses default arguments, allowing the following forms:
   * - No arguments: initializes both row and col to 0
   * - One argument: initializes row, col is set to 0
   * - Two arguments: initializes both row and col
   *
   * @param row The row coordinate (default: 0)
   * @param col The column coordinate (default: 0)
   */
    Coordinates(int64_t row = 0, int64_t col = 0) : row(row), col(col) {
    }

    /**
     *
     * @param other
     * @return
     */
    bool operator==(const Coordinates &other) const {
        return row == other.row && col == other.col;
    }
};

/**
 *
 */
struct Hash {

    /**
     *
     * @param x
     * @return
     */
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(const Coordinates& c) const {
        static const uint64_t FIXED_RANDOM =
            std::chrono::steady_clock::now().time_since_epoch().count();

        uint64_t h1 = Hash::splitmix64(c.row + FIXED_RANDOM);
        uint64_t h2 = Hash::splitmix64(c.col + FIXED_RANDOM);
        return h1 ^ (h2 << 1);
    }
};

/**
 * Represents an area of a table based on its from and to coordinates as a rectangle.
 * that above lft corner is from and below right corner is to coordinates.
 */
struct Area {
    Coordinates from;
    Coordinates to;

    /**
     * Constructs an area of from-to coordinates in a table.
     *
     * The constructor uses default arguments allowing the following forms:
     * - One argument: initializes row, col is set to default coordinates - both row and col equal to 0
     * - Two arguments: initializes both row and col
     *
     * @param from - upper-left corner's coordinates
     * @param to - bottom-right corner's coordinates
     */
    Area(Coordinates from, Coordinates to = Coordinates()) : from(from), to(to) {
    }

    /**
     * Finds the max of from and to row's coordinate.
     * @return the max row's coordinate.
     */
    int64_t maxRow() const {
        return std::max(from.row, to.row);
    }

    /**
     * Finds the max of from and to col's coordinate.
     * @return the max col's coordinate.
     */
    int64_t maxCol() const {
        return std::max(from.col, to.col);
    }
};

/**
 * Represents the cell structure as containing an expression, cachedValue and coordinates (coords).
 */
struct Cell {
    std::string expression;
    double cachedValue;
    Coordinates coords;

    /**
     * Constructs a cell via passing expression and coordinates. Sets the cachedValue to 0.o in the beginning before
     * the expression to be evaluated.
     *
     * @param expression the expression stored in the cell
     * @param coords the coordinates of the cell
     */
    Cell(const std::string &expression, const Coordinates coords) : expression(expression),
                                                                    cachedValue(0), coords(coords) {
    }
};

/**
 * Represents the type of the tokens in the expression.
 */
enum TokenType {
    End, // the end of the expression that should be tokenized
    Number, // the number value that is stored in the expression
    Plus, Minus, Mul, Div, Mod, // the operator value that is stored in the expression (+, -, *, / or %)
    LParen, RParen, // the parenthesis value that is stored in the expression - ( or )
    Comma, // the comma that is stored in the expression
    Equal, NotEqual, Less, Greater, // the comparison operator value that is stored in the expression (==, !=, < or >)
    Identifier, // the identifier value that is stored in the expression
    CellRef,
    // the cell reference that is stored in the expression (ex: R1C2, R[0]C5, R5C[0], R[-1]C10, R10C[-1] and so on)
};

/**
 * Represents the token in the expression.
 */
struct Token {
    TokenType type;
    std::string lexeme;

    /**
     * Constructs the token/s of the expression by initializing type and lexeme values.
     * @param type
     * @param lexeme
     */
    Token(const TokenType type, const std::string &lexeme) : type(type), lexeme(lexeme) {
    }
};

#endif //TYPES_H
