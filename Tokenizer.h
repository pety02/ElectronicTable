//
// Created by User on 1/20/2026.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <optional>

#include "Types.h"

/**
 * Tokenizer is responsible for converting a string expression
 * into a sequence of tokens that can later be parsed and evaluated.
 *
 * It performs lexical analysis by reading the input character by character
 * and grouping them into meaningful tokens such as numbers, operators,
 * identifiers, and cell references.
 */
class Tokenizer {
    const std::string &input;
    size_t pos;

    /**
     * Skips all whitespace characters starting from the current position.
     * Advances the internal position until a non-whitespace character
     * or the end of the input is reached.
     */
    void skipWhitespace();

    /**
     * Attempts to tokenize a numeric literal starting at the current position.
     *
     * @return An optional Token of type Number if successful,
     *         or std::nullopt if the current character does not start a number.
     */
    std::optional<Token> tokenizeNumber();

    /**
     * Attempts to tokenize a cell reference of the form RxCy, where
     * x and y can be absolute or relative (e.g. R5C3, R[-1]C[0]).
     *
     * @return An optional Token of type CellRef if successful,
     *         or std::nullopt if the current character does not start a cell reference.
     *
     * @throws std::runtime_error if the cell reference syntax is invalid.
     */
    std::optional<Token> tokenizeCellReference();

    /**
     * Attempts to tokenize an identifier, such as a function name
     * (e.g. sum, if, and, or, not).
     *
     * @return An optional Token of type Identifier if successful,
     *         or std::nullopt if the current character does not start an identifier.
     */
    std::optional<Token> tokenizeIdentifier();

    /**
     * Tokenizes operators and punctuation characters such as
     * +, -, *, /, %, parentheses, commas, and comparison operators.
     *
     * @return A Token representing the operator or punctuation.
     *
     * @throws std::runtime_error if an unexpected character is encountered.
     */
    Token tokenizeOperator();

public:
    /**
     * Constructs a Tokenizer for the given input expression.
     *
     * @param input The string expression to be tokenized.
     */
    Tokenizer(const std::string &input);

    /**
     * Returns the next token from the input expression.
     * Whitespace is skipped automatically.
     *
     * @return The next Token in the sequence, or a token of type End
     *         if the end of the input has been reached.
     */
    Token next();
};

#endif //TOKENIZER_H