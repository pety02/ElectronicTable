//
// Created by User on 1/20/2026.
//

#include "Tokenizer.h"
#include <stdexcept>

void Tokenizer::skipWhitespace() {
    while (pos < input.size() && std::isspace(static_cast<unsigned char>(input[pos]))) {
        ++pos;
    }
}

std::optional<Token> Tokenizer::tokenizeNumber() {
    if (!std::isdigit(input[pos])) {
        return std::nullopt;
    }

    size_t start = pos;
    while (pos < input.size() && std::isdigit(input[pos])) {
        ++pos;
    }

    return Token{TokenType::Number, input.substr(start, pos - start)};
}

std::optional<Token> Tokenizer::tokenizeCellReference() {
    if (input[pos] != 'R') {
        return std::nullopt;
    }

    size_t start = pos++;

    auto parseIndex = [&]() {
        if (pos < input.size() && input[pos] == '[') {
            ++pos;
            if (pos < input.size() && (input[pos] == '-' || std::isdigit(input[pos]))) {
                ++pos;
                while (pos < input.size() && std::isdigit(input[pos])) {
                    ++pos;
                }
            }
            if (pos >= input.size() || input[pos] != ']') {
                throw std::runtime_error("Invalid relative reference");
            }
            ++pos;
        } else {
            if (!std::isdigit(input[pos])) {
                throw std::runtime_error("Invalid absolute reference");
            }
            while (pos < input.size() && std::isdigit(input[pos])) {
                ++pos;
            }
        }
    };

    parseIndex();  // row

    if (pos >= input.size() || input[pos] != 'C') {
        throw std::runtime_error("Invalid cell reference (missing C)");
    }
    ++pos;

    parseIndex();  // column

    return Token{TokenType::CellRef, input.substr(start, pos - start)};
}

std::optional<Token> Tokenizer::tokenizeIdentifier() {
    if (!std::isalpha(static_cast<unsigned char>(input[pos]))) {
        return std::nullopt;
    }

    size_t start = pos++;
    while (pos < input.size() &&
           (std::isalnum(static_cast<unsigned char>(input[pos])) || input[pos] == '_')) {
        ++pos;
           }

    return Token{TokenType::Identifier, input.substr(start, pos - start)};
}

Token Tokenizer::tokenizeOperator() {
    char c = input[pos++];

    switch (c) {
        case '+': return {TokenType::Plus, "+"};
        case '-': return {TokenType::Minus, "-"};
        case '*': return {TokenType::Mul, "*"};
        case '/': return {TokenType::Div, "/"};
        case '%': return {TokenType::Mod, "%"};
        case '(': return {TokenType::LParen, "("};
        case ')': return {TokenType::RParen, ")"};
        case ',': return {TokenType::Comma, ","};

        case '=': {
            if (pos < input.size() && input[pos] == '=') {
                ++pos;
                return {TokenType::Equal, "=="};
            }
            break;
        }

        case '!': {
            if (pos < input.size() && input[pos] == '=') {
                ++pos;
                return {TokenType::NotEqual, "!="};
            }
            break;
        }

        case '<': return {TokenType::Less, "<"};
        case '>': return {TokenType::Greater, ">"};
        default: break;
    }

    throw std::runtime_error(std::string("Unexpected character: ") + c);
}

Tokenizer::Tokenizer(const std::string &input)
    : input(input), pos(0) {}

Token Tokenizer::next() {
    skipWhitespace();

    if (pos >= input.size()) {
        return {TokenType::End, ""};
    }

    if (auto t = tokenizeNumber())        return *t;
    if (auto t = tokenizeCellReference()) return *t;
    if (auto t = tokenizeIdentifier())    return *t;

    return tokenizeOperator();
}