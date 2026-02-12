//
// Created by Petya Licheva on 1/20/2026.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Types.h"

/**
 * @brief Performs lexical analysis of an expression string.
 *
 * Tokenizer converts a raw expression into a sequence of tokens
 * that can be consumed by the ExpressionParser. It recognizes
 * numeric literals, operators, identifiers, keywords, and cell
 * references, while ignoring whitespace.
 */
class Tokenizer {
    const std::string input; ///< Expression being tokenized
    size_t pos;               ///< Current position in the input string

    /**
     * @brief Skips whitespace characters.
     *
     * Advances the current position until a non-whitespace character
     * or the end of the input is reached.
     */
    void skipWhitespace();

    /**
     * @brief Attempts to tokenize a numeric literal.
     *
     * Supports integer and floating-point representations.
     *
     * @return Token of type Number if a numeric literal is found,
     *         otherwise std::nullopt
     */
    Token* tokenizeNumber();

    /**
     * @brief Attempts to tokenize a cell reference.
     *
     * Recognizes references of the form:
     * - Absolute: R5C3
     * - Relative: R[-1]C[0]
     *
     * @return Token of type CellRef if successful,
     *         otherwise std::nullopt
     *
     * @throws std::runtime_error if the syntax resembles a cell
     *         reference but is malformed.
     */
    Token* tokenizeCellReference();

    /**
     * @brief Attempts to tokenize an identifier.
     *
     * Identifiers may represent function names or logical keywords
     * such as `sum`, `if`, `and`, `or`, and `not`.
     *
     * @return Token of type Identifier if successful,
     *         otherwise std::nullopt
     */
    Token* tokenizeIdentifier();

    /**
     * @brief Tokenizes operators and punctuation.
     *
     * Handles:
     * - Arithmetic operators: +, -, *, /, %
     * - Comparison operators: ==, !=, <, >
     * - Parentheses: (, )
     * - Comma: ,
     *
     * @return Token representing the parsed operator or symbol
     *
     * @throws std::runtime_error if an unexpected character is encountered
     */
    Token tokenizeOperator();

public:
    /**
     * @brief Constructs a Tokenizer for an expression.
     *
     * @param input Expression string to tokenize
     */
    explicit Tokenizer(const std::string& input);

    /**
     * @brief Retrieves the next token from the input.
     *
     * Whitespace is skipped automatically. When the end of the input
     * is reached, a token of type End is returned.
     *
     * @return Next token in the sequence
     */
    Token next();
};

#endif // TOKENIZER_H