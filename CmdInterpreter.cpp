//
// Created by User on 1/20/2026.
//

#include "CmdInterpreter.h"

#include <fstream>
#include <algorithm>
#include <sstream>

void CmdInterpreter::save(const std::string &fileName, const Table& table) {
    std::ofstream out(fileName);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }

    const auto& cells = table.getCells();

    int64_t maxRow = 0;
    int64_t maxCol = 0;

    for (const auto& pair : cells) {
        const Cell& cell = pair.second;
        maxRow = std::max(maxRow, cell.coords.row);
        maxCol = std::max(maxCol, cell.coords.col);
    }

    for (int64_t r = 0; r <= maxRow; ++r) {
        for (int64_t c = 0; c <= maxCol; ++c) {
            Coordinates key = {r, c};
            auto it = cells.find(key);
            if (it != cells.end()) {
                out << it->second.expression;
            }

            if (c < maxCol) {
                out << ';';
            }
        }
        out << '\n';
    }
}

void CmdInterpreter::load(const std::string& fileName, Table& table) {
    std::ifstream in(fileName);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }

    std::string line;
    int64_t row = 0;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string cellExpr;
        int64_t col = 0;

        while (std::getline(ss, cellExpr, ';')) {
            if (!cellExpr.empty()) {
                table.set(Coordinates(row, col), cellExpr);
            }
            ++col;
        }

        ++row;
    }
}