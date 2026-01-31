//
// Created by User on 1/20/2026.
//

#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "Table.h"
#include "Tokenizer.h"

/**
 *
 */
class ExpressionParser {
    Tokenizer tokenizer;
    Token currentToken;
    const Table& table;
    Coordinates currentCellCoordinates;

    /**
     *
     */
    void advance();

public:
    /**
     * 
     * @param tokenizer 
     * @param token 
     * @param table 
     * @param currentCellCoordinates 
     */
    ExpressionParser(const Tokenizer& tokenizer, const Token& token,
                     const Table& table, const Coordinates& currentCellCoordinates);
    /**
     *
     * @param expression
     * @param table
     * @param cellCoordinates
     * @return
     */
    double evaluate(const std::string& expression,
                    const Table& table,
                    Coordinates cellCoordinates);

    /**
     *
     * @param c
     * @return
     */
    bool hasCell(Coordinates c) const;

    /**
     *
     * @param c
     * @return
     */
    double getValue(Coordinates c) const;

    /**
     *
     * @param c
     * @return
     */
    const std::string& getExpression(Coordinates c) const;

private:
    /**
     *
     * @return
     */
    double parseExpression();

    /**
     *
     * @return
     */
    double parseLogicalOr();

    /**
     *
     * @return
     */
    double parseLogicalAnd();

    /**
     *
     * @return
     */
    double parseEquality();

    /**
     *
     * @return
     */
    double parseComparison();

    /**
     *
     * @return
     */
    double parseTerm();

    /**
     *
     * @return
     */
    double parseFactor();

    /**
     *
     * @return
     */
    double parseUnary();

    /**
     *
     * @return
     */
    double parsePrimary();

    /**
     *
     * @return
     */
    double parseIf();

    /**
     *
     * @return
     */
    double parseCellReference();
};

#endif //EXPRESSION_PARSER_H