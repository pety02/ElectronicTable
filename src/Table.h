//
// Created by Petya Licheva on 1/19/2026.
//

#ifndef TABLE_H
#define TABLE_H

#include "Types.h"
#include <unordered_map>
#include <utility>

/**
 * @brief Represents a sparse two-dimensional table of cells.
 *
 * The table stores only non-empty cells internally, allowing efficient
 * handling of large tables with mostly empty entries.
 */
class Table {
private:
    std::unordered_map<Coordinates, Cell, Hash> cells; ///< Stored non-empty cells
    Coordinates focusedCoords; ///< Currently focused cell
    std::unordered_map<Coordinates, EvalState, Hash> evalState; ///< Stored states of the cells in the table

public:
    /**
     * @brief Computes the bounding rectangle of all non-empty cells.
     *
     * Determines the maximum row and column indices occupied by any cell.
     * If the table is empty, the returned values are implementation-defined.
     *
     * @return Pair of (maxRow, maxCol)
     */
    std::pair<int64_t, int64_t> findTableBounds() const;

    /**
     * @brief Constructs an empty table.
     *
     * Initially contains no cells.
     */
    Table();

    /**
     * @brief Sets or updates the expression of a cell.
     *
     * If the cell at the given coordinates does not exist, it is created.
     * Any previously cached value is expected to be recomputed on demand.
     *
     * @param coords Coordinates of the cell
     * @param expression Expression to store in the cell
     */
    void set(Coordinates coords, const std::string &expression);

    /**
     * @brief Retrieves the expression stored in a cell.
     *
     * @param coords Coordinates of the cell
     * @return Expression stored at the given coordinates
     *
     * @throws std::runtime_error if the cell does not exist
     */
    std::string get(Coordinates coords) const;

    /**
     * @brief Computes the sum of all non-empty cells in a rectangular area.
     *
     * Only cells that exist and contain expressions are considered.
     *
     * @param leftCell Upper-left corner of the area
     * @param rightCell Bottom-right corner of the area
     * @return Sum of evaluated cell values
     */
    double sum(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * @brief Counts non-empty cells in a rectangular area.
     *
     * @param leftCell Upper-left corner of the area
     * @param rightCell Bottom-right corner of the area
     * @return Number of existing cells within the area
     */
    int count(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * @brief Finds the minimum value among non-empty cells in a rectangular area.
     *
     * @param leftCell Upper-left corner of the area
     * @param rightCell Bottom-right corner of the area
     * @return Minimum evaluated value
     */
    double min(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * @brief Finds the maximum value among non-empty cells in a rectangular area.
     *
     * @param leftCell Upper-left corner of the area
     * @param rightCell Bottom-right corner of the area
     * @return Maximum evaluated value
     */
    double max(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * @brief Computes the average value of non-empty cells in a rectangular area.
     *
     * @param leftCell Upper-left corner of the area
     * @param rightCell Bottom-right corner of the area
     * @return Average evaluated value
     */
    double avg(Coordinates leftCell, Coordinates rightCell) const;

    /**
     * @brief Provides read-only access to all stored cells.
     * Intended for inspection, debugging, or iteration.
     *
     * @return Reference to the internal cell map
     */
    const std::unordered_map<Coordinates, Cell, Hash> &getCells() const;

    /**
    * @brief Finds the cached value of a cell in the table
    *
    * @param address the coordinates of the cell
    * @return the cached value
    */
    double getCachedValue(const Coordinates &address) const;

    /**
    * @brief Sets the calculated value as a cachedValue of a cell
    *
    * @param value calculatedValue of an expression
    * @param address
    */
    void setCachedValue(double value, const Coordinates &address);

    /**
     * @brief Checks if the cell is currently visited and if its value is being evaluated right now
     *
     * @param address the coordinates of the cell
     * @return if the cell currently is being evaluated
     */
    bool isBeingEvaluated(const Coordinates& address) const;

    /**
     * @brief Checks if the cell's evaluating is done
     *
     * @param address the coordinates of the cell
     * @return if the cell evaluation is done
     */
    bool isEvaluated(const Coordinates& address) const;

    /**
     * @brief Marks the cell as cell that soon will be evaluated. This
     * means that right now the process of evaluating is not started yet
     * but soon will start.
     *
     * @param address the address of the cell
     */
    void markEvaluating(const Coordinates& address);

    /**
     * @brief Marks the cell as evaluated.
     *
     * @param address the address of the cell
     */
    void markEvaluated(const Coordinates& address);

    /**
     * @brief Clears the evaluation state of the cell.
     *
     * @param address the address of the cell
     */
    void clearEvaluationState(const Coordinates& address);

    /**
     * @brief Invalidates the evaluation state of the whole table.
     */
    void invalidateEvalState();

};

#endif // TABLE_H