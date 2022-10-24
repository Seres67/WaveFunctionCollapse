//
// Created by Seres67 on 24/10/2022.
//

#ifndef WAVEFUNCTIONCOLLAPSE_TILESMANAGER_HPP
#define WAVEFUNCTIONCOLLAPSE_TILESMANAGER_HPP

#include <string>
#include <vector>
#include "utils/Random.hpp"

using ImageTile = struct ImageTile
{
    std::string image_path;
    std::vector<int> edges;
};

using GridTile = struct GridTile
{
    bool collapsed;
    std::vector<int> possible_states;
    int pos;

public:
    void collapse()
    {
        int state = possible_states[Random::getRandomInt(0, possible_states.size() - 1)];
        possible_states.clear();
        possible_states.push_back(state);
        collapsed = true;
    }
};

class TilesManager
{
public:
    static void createImageTile(std::string image_path);

    static size_t getImageTilesSize();

    static void setupEdges(const std::string &config_path);

    static ImageTile getImageTile(int state);

private:
    static std::vector<ImageTile> m_image_tiles;
};

#endif //WAVEFUNCTIONCOLLAPSE_TILESMANAGER_HPP
