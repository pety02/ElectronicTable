//
// Created by Petya Licheva on 1/20/2026.
//

#ifndef CMD_INTERPRETER_H
#define CMD_INTERPRETER_H

#include "Table.h"

/**
 * @brief Executes high-level user commands on a table instance.
 *
 * CmdInterpreter provides static utility functions that interpret
 * user commands and map them to corresponding Table and
 * ExpressionParser operations.
 */
class CmdInterpreter {
public:
 /**
  * @brief Saves a table to a CSV file.
  *
  * Only non-empty cells are written to the file. Each cell's
  * coordinates and stored expression are serialized.
  *
  * @param fileName Path to the output CSV file
  * @param table Table whose contents will be saved
  *
  * @throws std::runtime_error if the file cannot be opened or written
  */
 static void save(const std::string& fileName, const Table& table);

 /**
  * @brief Loads table contents from a CSV file.
  *
  * Existing table contents may be overwritten or extended,
  * depending on the implementation.
  *
  * @param fileName Path to the input CSV file
  * @param table Table into which the contents will be loaded
  *
  * @throws std::runtime_error if the file cannot be opened or parsed
  */
 static void load(const std::string& fileName, Table& table);

 /**
  * @brief Assigns an expression to a cell in the table.
  *
  * If the specified cell doesn’t exist, it will be created.
  *
  * @param address Target cell coordinates
  * @param expression Expression string to set
  * @param table Table where the cell resides
  */
 static void set(const Coordinates& address, const std::string& expression, Table& table);

 /**
  * @brief Prints evaluated numeric values for all cells within an area.
  *
  * Each cell’s expression is evaluated via ExpressionParser and
  * displayed in a grid-like output.
  *
  * @param area Area defining the rectangular region to print
  * @param table Source table containing the cells
  */
 static void printValue(const Area& area, const Table& table);

 /**
  * @brief Prints the raw expressions for all cells within an area.
  *
  * Similar to printValue(), but instead of evaluated values,
  * the original expressions are shown.
  *
  * @param area Area defining the rectangular region to print
  * @param table Source table containing the cells
  */
 static void printExpression(const Area& area, const Table& table);

 /**
  * @brief Prints evaluated values for all occupied cells in the table.
  *
  * The printed area automatically spans all non-empty cells detected
  * by findTableBounds().
  *
  * @param table Table to be displayed
  */
 static void printAllValues(const Table& table);

 /**
  * @brief Prints all expressions of the table in a grid format.
  *
  * Similar to printAllValues(), but displays stored expressions
  * instead of computed numeric values.
  *
  * @param table Table to be displayed
  */
 static void printAllExpressions(const Table& table);
};

#endif // CMD_INTERPRETER_H