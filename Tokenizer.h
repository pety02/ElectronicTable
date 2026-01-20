//
// Created by User on 1/20/2026.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Types.h"

/**
 *
 */
class Tokenizer {
    const std::string& input;
    size_t pos = 0;

public:
    /**
     *
     * @param s
     */
    Tokenizer(const std::string& s);

    /**
     *
     * @return
     */
    Token next();
};

#endif //TOKENIZER_H