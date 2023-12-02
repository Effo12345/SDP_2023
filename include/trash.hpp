#pragma once

#include "gameobject.hpp"
#include "renderobject.hpp"
#include <vector>
#include <array>

class Trash : public RenderObject, public GameObject {
    std::vector<std::shared_ptr<Sprite>> introAnim;
    std::shared_ptr<Sprite> sprite;
    Point spriteSize = {16.0f, 16.0f};

    std::array<Point, 4> spawnOffsets = {{{0, -5}, {0, -3}, {0, -6}, {0, -6}}};
    
    int targetY = 170;
    const float maxSpeed = 1.0f;   // Must stay constant for intro animation to work

    
    std::array<std::pair<std::string, int>, 4> trashFolders = {{
        {"images/trash0/", 9},
        {"images/trash1/", 6},
        {"images/trash2/", 10},
        {"images/trash3/", 11}
    }};
    int introIter {};


public:
    Trash(Point spawnLocation, int trashIndex = 0);

    void draw();
};