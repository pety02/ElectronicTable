//
// Created by User on 2/2/2026.
//
#include <catch2/catch_test_macros.hpp>
#include "../src/ExpressionParser.h"
#include "../src/Table.h"
#include "../src/Tokenizer.h"

TEST_CASE("Simple arithmetic parsing", "[parser]") {
    Table t;
    double val = ExpressionParser::evaluate("1+2*3", t, {0,0});
    REQUIRE(val == 7.0);

    val = ExpressionParser::evaluate("(1+2)*3", t, {0,0});
    REQUIRE(val == 9.0);
}

TEST_CASE("Boolean operators and if", "[parser]") {
    Table t;
    double val = ExpressionParser::evaluate("if(1==1,10,20)", t, {0,0});
    REQUIRE(val == 10.0);

    val = ExpressionParser::evaluate("if(1!=1,10,20)", t, {0,0});
    REQUIRE(val == 20.0);

    val = ExpressionParser::evaluate("1 and 0", t, {0,0});
    REQUIRE(val == 0.0);

    val = ExpressionParser::evaluate("1 or 0", t, {0,0});
    REQUIRE(val == 1.0);

    val = ExpressionParser::evaluate("not 0", t, {0,0});
    REQUIRE(val == 1.0);
}

TEST_CASE("Cell references", "[parser]") {
    Table t;
    t.set({0,0}, "10");
    t.set({0,1}, "20");

    auto cells = t.getCells();
    for (auto& [coords, cell] : cells) {
        cell.cachedValue = std::stod(cell.expression);
    }

    double val = ExpressionParser::evaluate("R0C0 + R0C1", t, {0,0});
    REQUIRE(val == 30.0);

    val = ExpressionParser::evaluate("R[0]C[1] - R[0]C[0]", t, {0,0});
    REQUIRE(val == 10.0);
}