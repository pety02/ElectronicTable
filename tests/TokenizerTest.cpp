//
// Created by Petya Licheva on 2/2/2026.
//
#include <catch2/catch_test_macros.hpp>
#include "../src/Tokenizer.h"

TEST_CASE("Tokenizer numbers", "[tokenizer]") {
    Tokenizer t("123 45");
    Token tok = t.next();
    REQUIRE(tok.type == TokenType::Number);
    REQUIRE(tok.lexeme == "123");

    tok = t.next();
    REQUIRE(tok.type == TokenType::Number);
    REQUIRE(tok.lexeme == "45");
}

TEST_CASE("Tokenizer cell references absolute and relative", "[tokenizer]") {
    Tokenizer t("R5C3 R[-1]C[0] R[-1]C3");

    Token tok = t.next();
    REQUIRE(tok.type == TokenType::CellRef);
    REQUIRE(tok.lexeme == "R5C3");

    tok = t.next();
    REQUIRE(tok.type == TokenType::CellRef);
    REQUIRE(tok.lexeme == "R[-1]C[0]");

    tok = t.next();
    REQUIRE(tok.type == TokenType::CellRef);
    REQUIRE(tok.lexeme == "R[-1]C3");
}

TEST_CASE("Tokenizer identifiers", "[tokenizer]") {
    Tokenizer t("sum avg if and or not foo123");

    Token tok = t.next();
    REQUIRE(tok.type == TokenType::Identifier);
    REQUIRE(tok.lexeme == "sum");

    tok = t.next();
    REQUIRE(tok.type == TokenType::Identifier);
    REQUIRE(tok.lexeme == "avg");

    tok = t.next();
    REQUIRE(tok.type == TokenType::Identifier);
    REQUIRE(tok.lexeme == "if");

    tok = t.next();
    REQUIRE(tok.type == TokenType::Identifier);
    REQUIRE(tok.lexeme == "and");

    tok = t.next();
    REQUIRE(tok.type == TokenType::Identifier);
    REQUIRE(tok.lexeme == "or");

    tok = t.next();
    REQUIRE(tok.type == TokenType::Identifier);
    REQUIRE(tok.lexeme == "not");

    tok = t.next();
    REQUIRE(tok.type == TokenType::Identifier);
    REQUIRE(tok.lexeme == "foo123");
}

TEST_CASE("Tokenizer operators", "[tokenizer]") {
    Tokenizer t("+-*/%(),==!=<>");
    Token tok;

    tok = t.next(); REQUIRE(tok.type == TokenType::Plus);
    tok = t.next(); REQUIRE(tok.type == TokenType::Minus);
    tok = t.next(); REQUIRE(tok.type == TokenType::Mul);
    tok = t.next(); REQUIRE(tok.type == TokenType::Div);
    tok = t.next(); REQUIRE(tok.type == TokenType::Mod);
    tok = t.next(); REQUIRE(tok.type == TokenType::LParen);
    tok = t.next(); REQUIRE(tok.type == TokenType::RParen);
    tok = t.next(); REQUIRE(tok.type == TokenType::Comma);
    tok = t.next(); REQUIRE(tok.type == TokenType::Equal);
    tok = t.next(); REQUIRE(tok.type == TokenType::NotEqual);
    tok = t.next(); REQUIRE(tok.type == TokenType::Less);
    tok = t.next(); REQUIRE(tok.type == TokenType::Greater);
    tok = t.next(); REQUIRE(tok.type == TokenType::End);
}