//
// Created by User on 1/20/2026.
//

#ifndef CMD_INTERPRETER_H
#define CMD_INTERPRETER_H

#include "Table.h"

/**
 * @brief Executes user commands over a table.
 *
 * CmdInterpreter maps high-level textual commands
 * (SET, PRINT, SAVE, LOAD) to operations on Table
 * and ExpressionParser.
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
 *
 */
 static void set(const Coordinates& address, const std::string& expression, Table& table);

 /**
 *
 */
 static void printValue(const Area& area, const Table& table);

 /**
 *
 */
 static void printExpression(const Area& area, const Table& table);

 /**
 *
 */
 static void printAllValues(const Table& table);

 /**
 *
 */
 static void printAllExpressions(const Table& table);
};

#endif // CMD_INTERPRETER_H