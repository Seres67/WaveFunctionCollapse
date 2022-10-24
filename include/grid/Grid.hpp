//
// Created by Seres67 on 24/10/2022.
//

#ifndef WAVEFUNCTIONCOLLAPSE_GRID_HPP
#define WAVEFUNCTIONCOLLAPSE_GRID_HPP

#include <map>
#include <manager/TilesManager.hpp>

class Grid
{
public:
    explicit Grid(int size, int max_states);

    void collapseTile(int pos);

    [[nodiscard]] int getSize() const;

    void setNeighboursStates(int pos);

    int getNextPos();

    bool isSolved();

    void display();

private:
    int m_size;
    std::vector<GridTile> m_grid;
};

#endif //WAVEFUNCTIONCOLLAPSE_GRID_HPP
