//
// Created by User on 1/20/2026.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <optional>

#include "Types.h"

/**
 *
 */
class Tokenizer {
    const std::string &input;
    size_t pos;

    /**
     *
     */
    void skipWhitespace();

    /**
     *
     * @return
     */
    std::optional<Token> tokenizeNumber();

    /**
     *
     * @return
     */
    std::optional<Token> tokenizeCellReference();

    /**
     *
     * @return
     */
    std::optional<Token> tokenizeIdentifier();

    /**
     *
     * @return
     */
    Token tokenizeOperator();

public:
    /**
     *
     * @param input
     */
    Tokenizer(const std::string &input);

    /**
     *
     * @return
     */
    Token next();
};


#endif //TOKENIZER_H