//
// Created by Petya Licheva on 1/20/2026.
//

#include "ExpressionParser.h"
#include <cmath>
#include <utility>

void ExpressionParser::advance() {
    this->currentToken = this->tokenizer.next();
}

ExpressionParser::ExpressionParser(const Tokenizer &tokenizer, Token token,
                                   Table &table,
                                   const Coordinates &currentCellCoordinates) : tokenizer(tokenizer),
    currentToken(std::move(token)), table(table), currentCellCoordinates(currentCellCoordinates) {
}

double ExpressionParser::evaluate(const std::string &expression,
                                  Table &table,
                                  Coordinates cellCoordinates) {
    Tokenizer tokenizer(expression);

    Token first = tokenizer.next();

    ExpressionParser parser(tokenizer, first, table, cellCoordinates);

    double result = parser.parseExpression();

    if (parser.currentToken.type != TokenType::End) {
        throw std::runtime_error("Unexpected token after end of expression");
    }

    return result;
}

bool ExpressionParser::hasCell(Coordinates c) const {
    return this->table.getCells().find(c) != table.getCells().end();
}

double ExpressionParser::getValue(Coordinates c) const {
    if (table.isBeingEvaluated(c)) {
        throw std::runtime_error("Circular reference detected");
    }

    if (table.isEvaluated(c)) {
        return table.getCachedValue(c);
    }

    table.markEvaluating(c);

    const auto& cell = table.getCells().at(c);

    double calculatedValue = ExpressionParser::evaluate(
        cell.expression,
        table,
        c
    );

    if(table.getCachedValue(c) == calculatedValue) {
        return calculatedValue;
    }

    table.markEvaluated(c);
    table.setCachedValue(calculatedValue, c);

    return calculatedValue;
}

const std::string &ExpressionParser::getExpression(Coordinates c) const {
    return this->table.getCells().at(c).expression;
}

double ExpressionParser::parseExpression() {
    return parseLogicalOr();
}

double ExpressionParser::parseLogicalOr() {
    double left = parseLogicalAnd();

    while (currentToken.type == TokenType::Identifier &&
           currentToken.lexeme == "or") {
        advance();

        if (left >= 1.0) {
            parseLogicalAnd();
            left = 1.0;
        } else {
            double right = parseEquality();
            left = (right >= 1.0) ? 1.0 : 0.0;
        }
    }

    return left;
}

double ExpressionParser::parseLogicalAnd() {
    double left = parseEquality();

    while (currentToken.type == TokenType::Identifier &&
           currentToken.lexeme == "and") {
        advance();

        if (left < 1.0) {
            parseEquality();
            left = 0.0;
        } else {
            double right = parseEquality();
            left = (right >= 1.0) ? 1.0 : 0.0;
        }
    }

    return left;
}

double ExpressionParser::parseEquality() {
    double left = parseComparison();

    while (currentToken.type == TokenType::Equal ||
           currentToken.type == TokenType::NotEqual) {
        TokenType op = currentToken.type;
        advance();

        double right = parseComparison();

        if (op == TokenType::Equal) {
            left = (left == right) ? 1.0 : 0.0;
        } else {
            left = (left != right) ? 1.0 : 0.0;
        }
    }

    return left;
}

double ExpressionParser::parseComparison() {
    double left = parseTerm();

    while (currentToken.type == TokenType::Less ||
           currentToken.type == TokenType::Greater) {
        TokenType op = currentToken.type;
        advance();

        double right = parseTerm();

        if (op == TokenType::Less) {
            left = (left < right) ? 1.0 : 0.0;
        } else {
            left = (left > right) ? 1.0 : 0.0;
        }
    }

    return left;
}

double ExpressionParser::parseTerm() {
    double left = parseFactor();

    while (currentToken.type == TokenType::Plus ||
           currentToken.type == TokenType::Minus) {

        TokenType op = currentToken.type;
        advance();

        double right = parseFactor();

        if (op == TokenType::Plus) {
            left += right;
        } else {
            left -= right;
        }
           }

    return left;
}

double ExpressionParser::parseFactor() {
    double left = parseUnary();

    while (currentToken.type == TokenType::Mul ||
           currentToken.type == TokenType::Div ||
           currentToken.type == TokenType::Mod) {

        TokenType op = currentToken.type;
        advance();

        double right = parseUnary();

        if (op == TokenType::Mul) {
            left *= right;
        } else if (op == TokenType::Div) {
            if (right == 0.0) {
                throw std::runtime_error("Division by zero");
            }
            left /= right;
        } else {
            left = std::fmod(left, right);
        }
           }

    return left;
}

double ExpressionParser::parseUnary() {
    if (currentToken.type == TokenType::Minus) {
        advance();
        return -parseUnary();
    }

    if (currentToken.type == TokenType::Identifier &&
        currentToken.lexeme == "not") {
        advance();
        double value = parseUnary();
        return (value < 1.0) ? 1.0 : 0.0;
        }

    return parsePrimary();
}

double ExpressionParser::parsePrimary() {
    if (currentToken.type == TokenType::Number) {
        double value = std::stod(currentToken.lexeme);
        advance();
        return value;
    }

    if (currentToken.type == TokenType::CellRef) {
        return parseCellReference();
    }

    if (currentToken.type == TokenType::Identifier &&
        currentToken.lexeme == "if") {
        return parseIf();
        }

    if (currentToken.type == TokenType::LParen) {
        advance();
        double value = parseExpression();

        if (currentToken.type != TokenType::RParen) {
            throw std::runtime_error("Expected ')'");
        }

        advance();
        return value;
    }

    throw std::runtime_error("Invalid primary expression");
}

double ExpressionParser::parseIf() {
    advance();

    if (currentToken.type != TokenType::LParen) {
        throw std::runtime_error("Expected '(' after if");
    }
    advance();

    double condition = parseExpression();

    if (currentToken.type != TokenType::Comma) {
        throw std::runtime_error("Expected ',' after condition");
    }
    advance();

    double trueBranch;
    double falseBranch;

    if (condition >= 1.0) {
        trueBranch = parseExpression();

        if (currentToken.type != TokenType::Comma) {
            throw std::runtime_error("Expected ',' in if");
        }
        advance();

        parseExpression();
    } else {
        parseExpression();

        if (currentToken.type != TokenType::Comma) {
            throw std::runtime_error("Expected ',' in if");
        }
        advance();

        falseBranch = parseExpression();
    }

    if (currentToken.type != TokenType::RParen) {
        throw std::runtime_error("Expected ')'");
    }
    advance();

    return (condition >= 1.0) ? trueBranch : falseBranch;
}

int64_t ExpressionParser::parseCoordPart(const std::string& s, size_t& pos, bool& isRelative) {
    if (s[pos] == '[') {
        isRelative = true;
        ++pos;

        size_t start = pos;
        if (s[pos] == '-') ++pos;
        while (pos < s.size() && std::isdigit(s[pos])) ++pos;

        int64_t value = std::stoll(s.substr(start, pos - start));

        if (pos >= s.size() || s[pos] != ']') {
            throw std::runtime_error("Invalid relative coordinate");
        }
        ++pos;
        return value;
    } else {
        isRelative = false;
        size_t start = pos;
        while (pos < s.size() && std::isdigit(s[pos])) ++pos;
        return std::stoll(s.substr(start, pos - start));
    }
}

double ExpressionParser::parseCellReference() {
    std::string ref = currentToken.lexeme;
    advance();

    size_t pos = 0;

    if (ref[pos] != 'R') {
        throw std::runtime_error("Invalid cell reference");
    }
    ++pos;

    bool rowRelative = false;
    int64_t rowValue = ExpressionParser::parseCoordPart(ref, pos, rowRelative);

    if (pos >= ref.size() || ref[pos] != 'C') {
        throw std::runtime_error("Invalid cell reference");
    }
    ++pos;

    bool colRelative = false;
    int64_t colValue = ExpressionParser::parseCoordPart(ref, pos, colRelative);

    Coordinates target;

    target.row = rowRelative
        ? currentCellCoordinates.row + rowValue
        : rowValue;

    target.col = colRelative
        ? currentCellCoordinates.col + colValue
        : colValue;

    if (!hasCell(target)) {
        throw std::runtime_error("Referenced cell does not exist");
    }

    return getValue(target);
}