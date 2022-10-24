//
// Created by Seres67 on 24/10/2022.
//

#include <iostream>
#include <filesystem>

#define cimg_use_png

#include <CImg.h>
#include <grid/Grid.hpp>
#include <manager/TilesManager.hpp>
#include <utils/Random.hpp>

void usage()
{
    std::cout << "Usage: ./wavefunctioncollapse <size> <tiles folder path>" << std::endl;
}

void renderImage(const Grid &grid)
{
    cimg_library::CImg<unsigned char> image(50 * grid.getSize(), 50 * grid.getSize(), 1, 3, 0);
    std::vector<cimg_library::CImg<unsigned char>> tiles;
    tiles.emplace_back(cimg_library::CImg<unsigned char>("../res/test/0.png"));
    tiles.emplace_back(cimg_library::CImg<unsigned char>("../res/test/1.png"));
    tiles.emplace_back(cimg_library::CImg<unsigned char>("../res/test/2.png"));
    tiles.emplace_back(cimg_library::CImg<unsigned char>("../res/test/3.png"));
    tiles.emplace_back(cimg_library::CImg<unsigned char>("../res/test/4.png"));
    for (int i = 0; i < grid.getSize() * grid.getSize(); ++i)
    {
        int x = i % grid.getSize();
        int y = i / grid.getSize();
        int state = grid.getTile(i).possible_states[0];
        image.draw_image(50 * x, 50 * y, tiles[state]);
    }
    image.save("../res/output.png");
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
    renderImage(grid);
    return 0;
}