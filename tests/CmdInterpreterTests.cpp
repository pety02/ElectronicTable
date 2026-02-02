//
// Created by User on 2/2/2026.
//
#include <catch2/catch_test_macros.hpp>
#include "../src/CmdInterpreter.h"
#include "../src/Table.h"
#include <fstream>

TEST_CASE("Save and load table", "[cmd]") {
    Table t;
    t.set({0,0}, "10");
    t.set({0,1}, "20");

    // Set cached values
    auto cells = t.getCells();
    for (auto& [coords, cell] : cells) {
        cell.cachedValue = std::stod(cell.expression);
    }

    std::string filename = "test_table.csv";

    // Save
    CmdInterpreter::save(filename, t);

    // Load into new table
    Table t2;
    CmdInterpreter::load(filename, t2);

    REQUIRE(t2.get({0,0}) == "10");
    REQUIRE(t2.get({0,1}) == "20");

    // Cleanup
    std::remove(filename.c_str());
}