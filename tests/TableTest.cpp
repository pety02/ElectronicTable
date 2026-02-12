//
// Created by Petya Licheva on 2/2/2026.
//
#include <catch2/catch_test_macros.hpp>
#include "../src/Table.h"

TEST_CASE("Table basic set and get", "[table]") {
    Table t;

    t.set({0,0}, "42");
    REQUIRE(t.get({0,0}) == "42");

    t.set({2,3}, "100");
    REQUIRE(t.get({2,3}) == "100");
}

TEST_CASE("Table focusedCoords behavior", "[table]") {
    Table t;

    t.set({0,0}, "1");
    t.set({-1,0}, "2"); // relative update

    REQUIRE(t.get({-1,0}) == "2");
}

TEST_CASE("Table aggregation functions", "[table]") {
    Table t;

    t.set({0,0}, "1");
    t.set({0,1}, "2");
    t.set({1,0}, "3");
    t.set({1,1}, "4");

    // Manually set cached values
    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= 1; ++j) {
            Coordinates coords{i,j};
            std::string cExpr=t.get(coords);
            t.setCachedValue(std::stod(cExpr),coords);
        }
    }

    REQUIRE(t.sum({0,0}, {1,1}) == 5.0);   // sum only uses two cells in your current impl
    REQUIRE(t.count({0,0}, {1,1}) == 4);   // count only checks two cells
    REQUIRE(t.min({0,0}, {1,1}) == 1.0);
    REQUIRE(t.max({0,0}, {1,1}) == 4.0);
    REQUIRE(t.avg({0,0}, {1,1}) == 2.5);
}