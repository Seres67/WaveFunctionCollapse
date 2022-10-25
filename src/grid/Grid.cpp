//
// Created by Seres67 on 24/10/2022.
//

#include <iostream>
#include <ranges>
#include "grid/Grid.hpp"

Grid::Grid(int size, int max_states) : m_size(size)
{
    std::vector<int> possible_states;
    for (int i = 0; i < max_states; ++i)
        possible_states.push_back(i);
    for (int i = 0; i < m_size * m_size; ++i)
        m_grid.emplace_back(GridTile{false, possible_states, i});
}

void Grid::collapseTile(int pos)
{
    m_grid[pos].collapse();
}

int Grid::getSize() const
{
    return m_size;
}

void Grid::setNeighboursStates(int pos)
{
    int x = pos % m_size;
    int y = pos / m_size;
    int left = pos - 1;
    int right = pos + 1;
    int top = pos - m_size;
    int bottom = pos + m_size;
    int state = m_grid[pos].possible_states[0];
    ImageTile curr = TilesManager::getImageTile(state);

    if (x > 0 && !m_grid[left].collapsed && left / m_size == y)
    {
        for (int i = 0; i < m_grid[left].possible_states.size(); ++i)
        {
            ImageTile tile = TilesManager::getImageTile(m_grid[left].possible_states[i]);
            if (curr.edges[3] != tile.edges[1] && m_grid[left].possible_states.size() > 1)
            {
                m_grid[left].possible_states.erase(m_grid[left].possible_states.begin() + i);
                --i;
            }
        }
    }
    if (x < m_size - 1 && !m_grid[right].collapsed && right / m_size == y)
    {
        for (int i = 0; i < m_grid[right].possible_states.size(); ++i)
        {
            ImageTile tile = TilesManager::getImageTile(m_grid[right].possible_states[i]);
            if (curr.edges[1] != tile.edges[3] && m_grid[right].possible_states.size() > 1)
            {
                m_grid[right].possible_states.erase(m_grid[right].possible_states.begin() + i);
                --i;
            }
        }
    }
    if (y > 0 && !m_grid[top].collapsed)
    {
        for (int i = 0; i < m_grid[top].possible_states.size(); ++i)
        {
            ImageTile tile = TilesManager::getImageTile(m_grid[top].possible_states[i]);
            if (curr.edges[0] != tile.edges[2] && m_grid[top].possible_states.size() > 1)
            {
                m_grid[top].possible_states.erase(m_grid[top].possible_states.begin() + i);
                --i;
            }
        }
    }
    if (y < m_size - 1 && !m_grid[bottom].collapsed)
    {
        for (int i = 0; i < m_grid[bottom].possible_states.size(); ++i)
        {
            ImageTile tile = TilesManager::getImageTile(m_grid[bottom].possible_states[i]);
            if (curr.edges[2] != tile.edges[0] && m_grid[bottom].possible_states.size() > 1)
            {
                m_grid[bottom].possible_states.erase(m_grid[bottom].possible_states.begin() + i);
                --i;
            }
        }
    }
}

int Grid::getNextPos()
{
    std::vector<GridTile> copy = m_grid;

    auto filter_collapsed = std::ranges::filter_view(copy, [](const GridTile &a)
    {
        return !a.collapsed;
    });
    std::vector only_collapsed(filter_collapsed.begin(), filter_collapsed.end());
    auto min = std::min_element(only_collapsed.begin(), only_collapsed.end(), [](const GridTile &a, const GridTile &b)
    { return a.possible_states.size() < b.possible_states.size(); });
    auto filter_min = std::ranges::filter_view(only_collapsed, [min](const GridTile &a)
    {
        return a.possible_states.size() == min->possible_states.size();
    });
    std::vector filtered(filter_min.begin(), filter_min.end());
    int rand = Random::getRandomInt(0, filtered.size() - 1);
    return filtered[rand].pos;
}

bool Grid::isSolved()
{
    for (int i = 0; i < m_size * m_size; ++i)
        if (!m_grid[i].collapsed)
            return false;
    return true;
}

void Grid::display()
{
    for (int i = 0; i < m_size * m_size; ++i)
    {
        if (i % m_size == 0)
            std::cout << std::endl;
        if (m_grid[i].collapsed)
            std::cout << m_grid[i].possible_states[0] << " ";
        else
            std::cout << "X ";
    }
    std::cout << std::endl;
}

GridTile Grid::getTile(int pos) const
{
    return m_grid[pos];
}