//
// Created by User on 1/20/2026.
//

#ifndef CMD_INTERPRETER_H
#define CMD_INTERPRETER_H

#include "Table.h"

/**
 *
 */
class CmdInterpreter {
public:
  /**
   *
   * @param fileName
   * @param table
   */
  static void save(std::string fileName, const Table& table);

  /**
   *
   * @param fileName
   * @param table
   */
  static void load(std::string fileName, Table& table);
};

#endif //CMD_INTERPRETER_H