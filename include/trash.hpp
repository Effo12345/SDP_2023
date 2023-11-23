#pragma once

#include "gameobject.hpp"
#include "renderobject.hpp"
#include <vector>
#include <array>

class Trash : public RenderObject, public GameObject {
    std::vector<std::shared_ptr<Sprite>> introAnim;
    std::shared_ptr<Sprite> sprite;
    Point spriteSize = {16.0f, 16.0f};

    std::array<Point, 3> spawnOffsets = {{{0, -5}, {0, -3}}};
    
    int targetY = 170;
    const float maxSpeed = 1.0f;   // Must stay constant for intro animation to work

    
    std::array<std::pair<std::string, int>, 3> trashFolders = {{
        {"images/trash0/", 9},
        {"images/trash1/", 6}
    }};
    int introIter {};


public:
    Trash(Point spawnLocation, int trashIndex = 0)
    : GameObject(spawnLocation, 1.0f) {
        setTarget(Point(spawnLocation.x, targetY));

        for(int i = 0; i < trashFolders[trashIndex].second; i++) {
            introAnim.push_back(
                std::make_shared<Sprite>(trashFolders[trashIndex].first + std::to_string(i + 1) + ".pic")
            );
        }

        gamePos = gamePos + spawnOffsets[trashIndex];

        sprite = std::make_shared<Sprite>(trashFolders[trashIndex].first + "full.pic");
    }

    void draw() {
        if(introIter < introAnim.size()) {
            introAnim[introIter]->setPos(gamePos - (spriteSize / 2));
            introAnim[introIter]->draw();

            introIter++;

            return;
        }

        sprite->setPos(gamePos - spriteSize / 2);
        sprite->draw();
    }
};