//
// Created by User on 1/19/2026.
//

#ifndef TABLE_H
#define TABLE_H

#include "Types.h"
#include <unordered_map>

/**
 * Represents a sparse rectangular table of cells.
 *
 * The table stores only non-empty cells internally, allowing it to handle
 * very large tables efficiently.
 */
class Table {
private:
    std::unordered_map<Coordinates, Cell, Hash> cells;
    Coordinates focusedCoords;

    /**
     * Finds the minimum bounding rectangle that contains all non-empty cells
     * in the table.
     *
     * @return A pair of values representing the maximum row and column indices.
     */
    std::pair<int64_t, int64_t> findTableBounds() const;

public:
    /**
     * Constructs an empty table.
     */
    Table();

    /**
     * Sets the expression of a cell at the given coordinates.
     * If the cell does not exist, it is created.
     *
     * @param coords The coordinates of the cell.
     * @param expression The expression to store in the cell.
     */
    void set(Coordinates coords, const std::string &expression);

    /**
     * Retrieves the expression stored in the cell at the given coordinates.
     *
     * @param coords The coordinates of the cell.
     * @return The expression stored in the cell.
     *
     * @throws std::runtime_error if the cell does not exist.
     */
    std::string get(Coordinates coords) const;

    /**
     * Prints the values of all cells within the given area.
     *
     * @param area The rectangular area to print.
     */
    void printVal(const Area &area) const;

    /**
     * Prints the expressions of all cells within the given area.
     *
     * @param area The rectangular area to print.
     */
    void printExpression(const Area &area) const;

    /**
     * Prints the values of all cells in the table, formatted by rows.
     */
    void printValAll() const;

    /**
     * Prints the expressions of all cells in the table, formatted by rows.
     */
    void printExpressionAll() const;

    /**
     * Computes the sum of the values of all non-empty cells
     * within the given rectangular area.
     */
    double sum(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * Counts the number of non-empty cells within the given rectangular area.
     */
    int count(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * Finds the minimum value among all non-empty cells
     * within the given rectangular area.
     */
    double min(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * Finds the maximum value among all non-empty cells
     * within the given rectangular area.
     */
    double max(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * Computes the average value of all non-empty cells
     * within the given rectangular area.
     */
    double avg(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * Provides read-only access to the internal map of cells.
     *
     * @return A constant reference to the internal cell map.
     */
    std::unordered_map<Coordinates, Cell, Hash> getCells() const;
};

#endif //TABLE_H