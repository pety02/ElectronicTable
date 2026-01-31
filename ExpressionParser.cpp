//
// Created by User on 1/20/2026.
//

#include "ExpressionParser.h"

void ExpressionParser::advance() {
    // TODO: to implement it
}

ExpressionParser::ExpressionParser(const Tokenizer& tokenizer, const Token& token,
                     const Table& table, const Coordinates& currentCellCoordinates) :
tokenizer(tokenizer), currentToken(token), table(table), currentCellCoordinates(currentCellCoordinates) {}

double ExpressionParser::evaluate(const std::string& expression,
                    const Table& table,
                    Coordinates cellCoordinates) {}

bool ExpressionParser::hasCell(Coordinates c) const {
    uint64_t key = Table::makeKey(c.row, c.col);
    return this->table.getCells().find(key) != table.getCells().end();
}

double ExpressionParser::getValue(Coordinates c) const {
    return this->table.getCells().at(Table::makeKey(c.row, c.col)).cachedValue;
}

const std::string& ExpressionParser::getExpression(Coordinates c) const {
    return this->table.getCells().at(Table::makeKey(c.row, c.col)).expression;
}

double ExpressionParser::parseExpression() {
    // TODO: to implement it
}

double ExpressionParser::parseLogicalOr() {
    // TODO: to implement it
}

double ExpressionParser::parseLogicalAnd() {
    // TODO: to implement it
}

double ExpressionParser::parseEquality() {
    // TODO: to implement it
}

double ExpressionParser::parseComparison() {
    // TODO: to implement it
}

double ExpressionParser::parseTerm() {
    // TODO: to implement it
}

double ExpressionParser::parseFactor() {
    // TODO: to implement it
}

double ExpressionParser::parseUnary() {
    // TODO: to implement it
}

double ExpressionParser::parsePrimary() {
    // TODO: to implement it
}

double ExpressionParser::parseIf() {
    // TODO: to implement it
}

double ExpressionParser::parseCellReference() {
    // TODO: to implement it
}