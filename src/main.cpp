#include <iostream>
#include "Table.h"
#include "ExpressionParser.h"
#include "CmdInterpreter.h"

int main() {
    try {
        Table table;

        // --- Set some expressions ---
        table.set(Coordinates(0, 0), "10");
        table.set(Coordinates(0, 1), "20");
        table.set(Coordinates(1, 0), "R0C0 + R0C1"); // sum of first row
        table.set(Coordinates(1, 1), "if(R0C0 > 5, 100, 0)");

        // --- Print values of a small area ---
        std::cout << "Values of cells (0,0) to (1,1):\n";
        table.printVal(Area(Coordinates(0,0), Coordinates(1,1)));

        // --- Save to CSV ---
        std::string filename = "table_test.csv";
        CmdInterpreter::save(filename, table);
        std::cout << "Table saved to " << filename << std::endl;

        // --- Load into a new table ---
        Table loadedTable;
        CmdInterpreter::load(filename, loadedTable);
        std::cout << "Loaded table values:\n";
        loadedTable.printValAll();

        // --- Evaluate a single expression using parser ---
        ExpressionParser parser(
            Tokenizer("R1C0 + R1C1"),        // tokenizer
            Tokenizer("R1C0 + R1C1").next(), // start token
            loadedTable,
            Coordinates(0,0)                  // current cell (top-left)
        );

        double result = parser.evaluate("R1C0 + R1C1", loadedTable, Coordinates(0,0));
        std::cout << "Evaluated R1C0 + R1C1 = " << result << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}