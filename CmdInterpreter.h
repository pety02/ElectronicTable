//
// Created by User on 1/20/2026.
//

#ifndef CMD_INTERPRETER_H
#define CMD_INTERPRETER_H

#include "Table.h"

/**
 * CmdInterpreter handles file-based input and output operations
 * for saving and loading the table contents.
 */
class CmdInterpreter {
public:
 /**
  * Saves the contents of the table to a file in CSV format.
  *
  * @param fileName The name of the output file.
  * @param table The table whose contents will be saved.
  */
 static void save(const std::string &fileName, const Table& table);

 /**
  * Loads table contents from a CSV file.
  *
  * @param fileName The name of the input file.
  * @param table The table into which the contents will be loaded.
  */
 static void load(const std::string& fileName, Table& table);
};

#endif //CMD_INTERPRETER_H