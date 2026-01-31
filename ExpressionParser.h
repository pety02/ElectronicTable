//
// Created by User on 1/20/2026.
//

#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "Table.h"
#include "Tokenizer.h"

/**
 * ExpressionParser evaluates arithmetic, logical, and functional expressions
 * used in table cells.
 *
 * It uses a recursive-descent parsing strategy and interacts with the Table
 * to resolve cell references and compute values.
 */
class ExpressionParser {
    Tokenizer tokenizer;
    Token currentToken;
    const Table &table;
    Coordinates currentCellCoordinates;

    /**
     * Advances to the next token in the token stream.
     * Updates currentToken to the next token.
     */
    void advance();

public:
    /**
     * Constructs an ExpressionParser with the required context.
     *
     * @param tokenizer The tokenizer used to read expression tokens.
     * @param token The initial token.
     * @param table The table used to resolve cell references.
     * @param currentCellCoordinates The coordinates of the currently evaluated cell.
     */
    ExpressionParser(const Tokenizer &tokenizer, const Token &token,
                     const Table &table, const Coordinates &currentCellCoordinates);

    /**
     * Evaluates the given expression in the context of the specified table
     * and cell coordinates.
     *
     * @param expression The expression to evaluate.
     * @param table The table providing cell values.
     * @param cellCoordinates The coordinates of the evaluated cell.
     * @return The numeric result of the evaluation.
     */
    static double evaluate(const std::string &expression,
                           const Table &table,
                           Coordinates cellCoordinates);

    /**
     * Checks whether a cell exists at the given coordinates.
     */
    bool hasCell(Coordinates c) const;

    /**
     * Retrieves the value of the cell at the given coordinates.
     */
    double getValue(Coordinates c) const;

    /**
     * Retrieves the expression stored in the cell at the given coordinates.
     */
    const std::string &getExpression(Coordinates c) const;

private:
    /**
     * Parses a full expression, handling logical OR operations as the top-level operator.
     *
     * @return The computed value of the parsed expression.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseExpression();

    /**
     * Parses logical OR expressions (operator `or`) with left-to-right associativity.
     *
     * @return The computed value of the parsed logical OR expression.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseLogicalOr();

    /**
     * Parses logical AND expressions (operator `and`) with left-to-right associativity.
     *
     * @return The computed value of the parsed logical AND expression.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseLogicalAnd();

    /**
     * Parses equality expressions (operators `==` and `!=`) with left-to-right associativity.
     *
     * @return The computed value of the parsed equality expression.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseEquality();

    /**
     * Parses comparison expressions (operators `<` and `>`) with left-to-right associativity.
     *
     * @return The computed value of the parsed comparison expression.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseComparison();

    /**
     * Parses addition and subtraction expressions (operators `+` and `-`)
     * with left-to-right associativity.
     *
     * @return The computed value of the parsed term.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseTerm();

    /**
     * Parses multiplication, division, and modulo expressions (operators `*`, `/`, `%`)
     * with left-to-right associativity.
     *
     * @return The computed value of the parsed factor.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseFactor();

    /**
     * Parses unary operators such as `+`, `-`, and `not`.
     *
     * @return The computed value of the unary expression.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseUnary();

    /**
     * Parses primary expressions, which may be:
     * - numeric literals
     * - parenthesized sub-expressions
     * - identifiers (functions)
     * - cell references
     *
     * @return The computed value of the primary expression.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parsePrimary();

    /**
     * Parses an if-expression of the form: if(condition, true_value, false_value)
     *
     * @return The value of true_value if the condition is non-zero,
     * otherwise the value of false_value.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseIf();

    /**
     * 
     * @param s 
     * @param pos 
     * @param isRelative 
     * @return 
     */
    static int64_t parseCoordPart(const std::string& s, size_t& pos, bool& isRelative);
 
    /**
     * Parses a cell reference token and retrieves the value from the table.
     * Handles both absolute and relative references based on currentCellCoordinates.
     *
     * @return The numeric value of the referenced cell.
     * - 1.0 for true
     * - 0.0 for false
     */
    double parseCellReference();
};

#endif //EXPRESSION_PARSER_H
