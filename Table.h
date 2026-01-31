//
// Created by User on 1/19/2026.
//

#ifndef TABLE_H
#define TABLE_H

#include "Types.h"
#include <unordered_map>
#include <stdexcept>

/**
 *
 */
class Table {
private:
    std::unordered_map<uint64_t, Cell> cells;
    Coordinates focusedCoords;

public:
    /**
     *
     * @param r
     * @param c
     * @return
     */
    static uint64_t makeKey(int64_t r, int64_t c);

private:
    /**
    *
    * @return
    */
    std::pair<int64_t, int64_t> findTableBounds() const;

public:
    /**
     *
     */
    Table();

    /**
     *
     * @param coords
     * @param expression
     */
    void set(Coordinates coords, const std::string &expression);

    /**
     *
     * @param coords
     * @return
     */
    std::string get(Coordinates coords) const;

    /**
     *
     * @param area
     */
    void printVal(Area area) const;

    /**
     *
     * @param area
     */
    void printExpression(Area area) const;

    /**
     *
     */
    void printValAll() const;

    /**
     *
     */
    void printExpressionAll() const;

    /**
     *
     * @param leftCell
     * @param rightCell
     * @return
     */
    double sum(Coordinates leftCell, Coordinates rightCell) const;

    /**
     *
     * @param leftCell
     * @param rightCell
     * @return
     */
    int count(Coordinates leftCell, Coordinates rightCell) const;

    /**
     *
     * @param leftCell
     * @param rightCell
     * @return
     */
    double min(Coordinates leftCell, Coordinates rightCell) const;

    /**
     *
     * @param leftCell
     * @param rightCell
     * @return
     */
    double max(Coordinates leftCell, Coordinates rightCell) const;

    /**
     *
     * @param leftCell
     * @param rightCell
     * @return
     */
    double avg(Coordinates leftCell, Coordinates rightCell) const;

    /**
     *
     * @return
     */
    const std::unordered_map<uint64_t, Cell> getCells() const;
};

#endif //TABLE_H
