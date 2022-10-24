//
// Created by Seres67 on 24/10/2022.
//

#include <utility>
#include <fstream>
#include "manager/TilesManager.hpp"

std::vector<ImageTile> TilesManager::m_image_tiles;

void TilesManager::createImageTile(std::string image_path)
{
    m_image_tiles.push_back(ImageTile{std::move(image_path)});
}

size_t TilesManager::getImageTilesSize()
{
    return m_image_tiles.size();
}

void TilesManager::setupEdges(const std::string &config_path)
{
    std::ifstream file(config_path, std::ios::in);

    std::string line;
    while (std::getline(file, line))
    {
        std::string image_name = line.substr(0, line.find(' '));
        std::string edges = line.substr(line.find(' ') + 1, line.size());

        for (auto &image_tile: m_image_tiles)
        {
            std::string tile_image_name = image_tile.image_path.substr(image_tile.image_path.find_last_of("/\\") + 1, image_tile.image_path.size());
            if (tile_image_name == image_name)
            {
                for (int i = 0; i < 4; ++i)
                {
                    std::string edge = edges.substr(0, edges.find(' '));
                    edges = edges.substr(edges.find(' ') + 1, edges.size());
                    image_tile.edges.push_back(std::stoi(edge));
                }
            }
        }
    }
}

ImageTile TilesManager::getImageTile(int state)
{
    return m_image_tiles[state];
}