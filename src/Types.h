//
// Created by User on 1/19/2026.
//

#ifndef TYPES_H
#define TYPES_H

#include <chrono>
#include <cstdint>
#include <string>
#include <algorithm>

/**
 * @brief Represents a position in a table.
 *
 * A coordinate consists of a row index and a column index.
 * Rows and columns are zero-based unless specified otherwise
 * by the surrounding logic.
 */
struct Coordinates {
    int64_t row; ///< Row index
    int64_t col; ///< Column index

    /**
     * @brief Constructs a Coordinates object.
     *
     * Supported forms:
     * - Coordinates()            -> (0, 0)
     * - Coordinates(row)         -> (row, 0)
     * - Coordinates(row, col)    -> (row, col)
     *
     * @param row Row index (default: 0)
     * @param col Column index (default: 0)
     */
    Coordinates(int64_t row = 0, int64_t col = 0)
        : row(row), col(col) {}

    /**
     * @brief Equality comparison operator.
     *
     * @param other Another Coordinates object
     * @return true if both row and column are equal
     */
    bool operator==(const Coordinates& other) const {
        return row == other.row && col == other.col;
    }
};

/**
 * @brief Hash functor for Coordinates.
 *
 * Intended for use with unordered containers
 * (e.g., std::unordered_map, std::unordered_set).
 */
struct Hash {

    /**
     * @brief SplitMix64 hash function.
     *
     * Produces a high-quality 64-bit hash from a 64-bit input.
     * Based on the reference implementation - written in 2015
     * by Sebastiano Vigna (vigna@acm.org):
     * http://xorshift.di.unimi.it/splitmix64.c
     *
     * @param x Input value
     * @return Hashed value
     */
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    /**
     * @brief Computes a hash value for Coordinates.
     *
     * A fixed random seed is used to reduce hash collision
     * attacks and improve distribution.
     *
     * @param c Coordinates to hash
     * @return Hash value
     */
    size_t operator()(const Coordinates& c) const {
        static const uint64_t FIXED_RANDOM =
            std::chrono::steady_clock::now().time_since_epoch().count();

        uint64_t h1 = splitmix64(static_cast<uint64_t>(c.row) + FIXED_RANDOM);
        uint64_t h2 = splitmix64(static_cast<uint64_t>(c.col) + FIXED_RANDOM);
        return h1 ^ (h2 << 1);
    }
};

/**
 * @brief Represents a rectangular area in a table.
 *
 * The rectangle is defined by two coordinates:
 * - `from`: upper-left corner
 * - `to`:   bottom-right corner
 *
 * Ordering is not enforced; helper functions compute bounds safely.
 */
struct Area {
    Coordinates from; ///< Upper-left corner
    Coordinates to;   ///< Bottom-right corner

    /**
     * @brief Constructs a table area.
     *
     * Supported forms:
     * - Area(from)         -> `to` defaults to (0, 0)
     * - Area(from, to)     -> explicit rectangle
     *
     * @param from Upper-left corner coordinates
     * @param to Bottom-right corner coordinates (default: (0, 0))
     */
    Area(Coordinates from, Coordinates to = Coordinates())
        : from(from), to(to) {}

    /**
     * @brief Returns the maximum row index covered by the area.
     *
     * @return Maximum row value between `from` and `to`
     */
    int64_t maxRow() const {
        return std::max(from.row, to.row);
    }

    /**
     * @brief Returns the maximum column index covered by the area.
     *
     * @return Maximum column value between `from` and `to`
     */
    int64_t maxCol() const {
        return std::max(from.col, to.col);
    }
};

/**
 * @brief Represents a spreadsheet cell.
 *
 * A cell stores:
 * - The original expression
 * - A cached numeric value (after evaluation)
 * - Its position in the table
 */
struct Cell {
    std::string expression; ///< Raw expression text
    double cachedValue;     ///< Cached evaluation result
    Coordinates coords;     ///< Cell position

    /**
     * @brief Constructs a Cell.
     *
     * The cached value is initialized to 0.0 and is expected
     * to be updated after expression evaluation.
     *
     * @param expression Expression stored in the cell
     * @param coords Coordinates of the cell
     */
    Cell(const std::string& expression, Coordinates coords)
        : expression(expression), cachedValue(0.0), coords(coords) {}
};

/**
 * @brief Token types used during expression tokenization.
 */
enum TokenType {
    End,        ///< End of input
    Number,     ///< Numeric literal
    Plus,       ///< '+'
    Minus,      ///< '-'
    Mul,        ///< '*'
    Div,        ///< '/'
    Mod,        ///< '%'
    LParen,     ///< '('
    RParen,     ///< ')'
    Comma,      ///< ','
    Equal,      ///< '=='
    NotEqual,   ///< '!='
    Less,       ///< '<'
    Greater,    ///< '>'
    Identifier, ///< Function or variable identifier
    CellRef     ///< Cell reference (e.g., R1C2, R[-1]C5)
};

/**
 * @brief Represents a single token in an expression.
 */
struct Token {
    TokenType type;     ///< Token category
    std::string lexeme; ///< Raw token text

    /**
     * @brief Constructs a Token.
     *
     * @param type Token type
     * @param lexeme Token text as it appears in the expression
     */
    Token(TokenType type, const std::string& lexeme)
        : type(type), lexeme(lexeme) {}
};

#endif // TYPES_H