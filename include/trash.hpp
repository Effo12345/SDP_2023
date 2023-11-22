#pragma once

#include "gameobject.hpp"
#include "renderobject.hpp"
#include <vector>
#include <array>

// TODO
// TODO
// TODO
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Add sprite size offset to render position

class Trash : public RenderObject, public GameObject {
    std::vector<std::shared_ptr<Sprite>> introAnim;
    std::shared_ptr<Sprite> sprite;
    
    int targetY = 200;

    
    std::array<std::pair<std::string, int>, 3> trashFolders = {{
        {"images/trash0/", 9},
        {"images/trash1/", 3},
        {"images/trash2/", 6}
    }};
    int introIter {};


public:
    Trash(Point spawnLocation, float maxSpeed = 1.0f, int trashIndex = 0)
    : GameObject(spawnLocation, maxSpeed) {
        setTarget(Point(spawnLocation.x, targetY));

        for(int i = 0; i < trashFolders[trashIndex].second; i++) {
            introAnim.push_back(
                std::make_shared<Sprite>(trashFolders[trashIndex].first + std::to_string(i + 1) + ".pic")
            );
        }

        sprite = std::make_shared<Sprite>(trashFolders[trashIndex].first = "full.pic");
    }

    void draw() {
        if(introIter < introAnim.size()) {
            introAnim[introIter]->setPos(gamePos);   // TODO Fix render pos offset
            introAnim[introIter]->draw();

            return;
        }

        sprite->setPos(gamePos);                     // TODO Fix render pos offset
        sprite->draw();
    }
};