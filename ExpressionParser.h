//
// Created by User on 1/20/2026.
//

#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "Table.h"
#include "Tokenizer.h"

/**
 * @brief Evaluates arithmetic, logical, and functional expressions used in table cells.
 *
 * ExpressionParser implements a recursive-descent parser that respects
 * operator precedence and associativity. It evaluates expressions in the
 * context of a table, allowing access to other cells via absolute and
 * relative references.
 */
class ExpressionParser {
    Tokenizer tokenizer;                 ///< Token stream for the expression
    Token currentToken;                  ///< Currently processed token
    const Table& table;                  ///< Table used to resolve cell references
    Coordinates currentCellCoordinates;  ///< Coordinates of the evaluated cell

    /**
     * @brief Advances to the next token in the token stream.
     *
     * Updates currentToken with the next token produced by the tokenizer.
     */
    void advance();

public:
    /**
     * @brief Constructs an ExpressionParser.
     *
     * @param tokenizer Tokenizer initialized with the expression
     * @param token Initial token (typically the first token)
     * @param table Table used to resolve referenced cells
     * @param currentCellCoordinates Coordinates of the currently evaluated cell
     */
    ExpressionParser(const Tokenizer& tokenizer,
                     Token token,
                     const Table& table,
                     const Coordinates& currentCellCoordinates);

    /**
     * @brief Evaluates an expression in the context of a table cell.
     *
     * This is the main entry point for expression evaluation.
     *
     * @param expression Expression string to evaluate
     * @param table Table providing referenced cell values
     * @param cellCoordinates Coordinates of the evaluated cell
     * @return Numeric result of the evaluation
     */
    static double evaluate(const std::string& expression,
                           const Table& table,
                           Coordinates cellCoordinates);

    /**
     * @brief Checks whether a cell exists at the given coordinates.
     *
     * @param c Cell coordinates
     * @return true if the cell exists, false otherwise
     */
    [[nodiscard]] bool hasCell(Coordinates c) const;

    /**
     * @brief Retrieves the cached value of a cell.
     *
     * @param c Cell coordinates
     * @return Numeric value stored in the cell
     */
    [[nodiscard]] double getValue(Coordinates c) const;

    /**
     * @brief Retrieves the raw expression stored in a cell.
     *
     * @param c Cell coordinates
     * @return Reference to the cell's expression string
     */
    [[nodiscard]] const std::string& getExpression(Coordinates c) const;

private:
    /**
     * @brief Parses a complete expression.
     *
     * This is the top-level parsing function and represents
     * the lowest-precedence rule in the grammar.
     *
     * @return Computed expression value
     */
    double parseExpression();

    /**
     * @brief Parses logical OR expressions (`or`).
     *
     * Left-to-right associative.
     *
     * @return 1.0 if true, 0.0 if false
     */
    double parseLogicalOr();

    /**
     * @brief Parses logical AND expressions (`and`).
     *
     * Left-to-right associative.
     *
     * @return 1.0 if true, 0.0 if false
     */
    double parseLogicalAnd();

    /**
     * @brief Parses equality expressions (`==`, `!=`).
     *
     * Left-to-right associative.
     *
     * @return 1.0 if true, 0.0 if false
     */
    double parseEquality();

    /**
     * @brief Parses comparison expressions (`<`, `>`).
     *
     * Left-to-right associative.
     *
     * @return 1.0 if true, 0.0 if false
     */
    double parseComparison();

    /**
     * @brief Parses addition and subtraction (`+`, `-`).
     *
     * Left-to-right associative.
     *
     * @return Computed numeric value
     */
    double parseTerm();

    /**
     * @brief Parses multiplication, division, and modulo (`*`, `/`, `%`).
     *
     * Left-to-right associative.
     *
     * @return Computed numeric value
     */
    double parseFactor();

    /**
     * @brief Parses unary expressions.
     *
     * Handles unary operators such as:
     * - unary plus (`+`)
     * - unary minus (`-`)
     * - logical not (`not`)
     *
     * @return Computed numeric value
     */
    double parseUnary();

    /**
     * @brief Parses primary expressions.
     *
     * Primary expressions include:
     * - numeric literals
     * - parenthesized expressions
     * - identifiers (functions)
     * - cell references
     *
     * @return Computed numeric value
     */
    double parsePrimary();

    /**
     * @brief Parses an if-expression.
     *
     * Syntax:
     * if(condition, true_value, false_value)
     *
     * @return true_value if condition is non-zero,
     * otherwise false_value
     */
    double parseIf();

    /**
     * @brief Parses a single coordinate component of a cell reference.
     *
     * Parses row or column parts such as:
     * - Absolute:  R5, C10
     * - Relative:  R[0], C[-1]
     *
     * Advances the parsing position accordingly and reports
     * whether the coordinate is relative.
     *
     * @param s Full cell reference string
     * @param pos Current parsing position (updated during parsing)
     * @param isRelative Set to true if the coordinate is relative
     * @return Parsed coordinate value
     */
    static int64_t parseCoordPart(const std::string& s,
                                  size_t& pos,
                                  bool& isRelative);

    /**
     * @brief Parses a cell reference and retrieves its value.
     *
     * Supports both absolute and relative references (e.g., R1C2,
     * R[-1]C[0]) resolved relative to currentCellCoordinates.
     *
     * @return Numeric value of the referenced cell
     */
    double parseCellReference();
};

#endif // EXPRESSION_PARSER_H