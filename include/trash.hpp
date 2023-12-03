#pragma once

#include "gameobject.hpp"
#include "renderobject.hpp"
#include <vector>
#include <array>

/**
 * @author Ethan Rosati
 * 
 * Class that manages the appearance and behavior of trash objects. Handles 
 * movement and rendering through inheritance
 **/
class Trash : public RenderObject, public GameObject {
    // Sprites to be used while the trash is entering from top of screen
    std::vector<std::shared_ptr<Sprite>> introAnim;
    // Full sprite
    std::shared_ptr<Sprite> sprite;
    Point spriteSize = {16.0f, 16.0f};

    // Each trash has a different vertical size so its spawn location must be 
    // offset relative to the class' instantiation position.
    std::array<Point, 4> spawnOffsets = {{{0, -5}, {0, -3}, {0, -6}, {0, -6}}};
    
    // The trash moves towards the beach then stops
    int targetY = 170;
    static const int maxSpeed = 1;   // Must stay constant for intro animation to work

    // Each piece of trash has a folder that stores its sprites
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