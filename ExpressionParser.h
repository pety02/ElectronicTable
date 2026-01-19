//
// Created by User on 1/20/2026.
//

#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "Table.h"
#include "Tokenizer.h"

class ExpressionParser {
    Tokenizer tokenizer;
    Token currentToken;
    const Table& table;
    Coordinates currentCellCoordinates;

    void advance();

public:
    double evaluate(const std::string& expression,
                    const Table& token,
                    Coordinates cellCoordinates);

    bool hasCell(Coordinates c) const;
    double getValue(Coordinates c) const;
    const std::string& getExpression(Coordinates c) const;

private:
    double parseExpression();
    double parseLogicalOr();
    double parseLogicalAnd();
    double parseEquality();
    double parseComparison();
    double parseTerm();
    double parseFactor();
    double parseUnary();
    double parsePrimary();
    double parseIf();
    double parseCellReference();
};

#endif //EXPRESSION_PARSER_H