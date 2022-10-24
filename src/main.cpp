//
// Created by Seres67 on 24/10/2022.
//

#include <iostream>
#include <filesystem>
#include <grid/Grid.hpp>
#include <manager/TilesManager.hpp>
#include <utils/Random.hpp>

void usage()
{
    std::cout << "Usage: ./wavefunctioncollapse <size> <tiles folder path>" << std::endl;
}

int main(int ac, char *av[])
{
    if (ac != 3)
    {
        usage();
        return 0;
    }

    std::filesystem::path path(av[2]);
    for (const auto &entry: std::filesystem::directory_iterator(path))
        if (entry.path().extension() == ".png")
            TilesManager::createImageTile(entry.path().string());
    TilesManager::setupEdges(path.string() + "/tileset.cfg");

    Grid grid(std::stoi(av[1]), static_cast<int>(TilesManager::getImageTilesSize()));

    Random::initialize(static_cast<int>(TilesManager::getImageTilesSize()));

    int pos = Random::getRandomInt(0, grid.getSize() * grid.getSize() - 1);
    grid.collapseTile(pos);
    grid.setNeighboursStates(pos);
    for (int i = 0; !grid.isSolved(); ++i)
    {
        pos = grid.getNextPos();
        grid.collapseTile(pos);
        grid.setNeighboursStates(pos);
    }
    grid.display();
    return 0;
}