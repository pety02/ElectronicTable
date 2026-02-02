//
// Created by User on 1/20/2026.
//

#ifndef CMD_INTERPRETER_H
#define CMD_INTERPRETER_H

#include "Table.h"

/**
 * @brief Handles file-based input and output for tables.
 *
 * CmdInterpreter provides utilities for persisting table contents
 * to disk and restoring them later using a CSV-based format.
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
};

#endif // CMD_INTERPRETER_H