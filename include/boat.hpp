#pragma once

#include "gameobject.hpp"
#include <vector>
#include <array>
#include <float.h>

class Boat : public GameObject {
    int currentSprite {};
    std::vector<std::shared_ptr<Sprite>> sprites;

    void updateSprite() {
        std::array<float, 4> angleReferences = {0, M_PI / 2, M_PI, 3 * M_PI / 2};
        

        float smallestDelta = FLT_MAX;
        int smallestIndex {};
        for(int i = 0; i < angleReferences.size(); i++) {
            float delta = fabs(angleReferences[i] - targetAngle);

            if(delta < smallestDelta) {
                smallestDelta = delta;
                smallestIndex = i;
            }

            std::cout << smallestIndex << ", " << targetAngle << "\n";
        }

        

        currentSprite = smallestIndex;

        for(auto& s : sprites) {
            s->setPos(sprite->getPos());
        }
    }

public:
    Boat(std::vector<char*> spriteFiles, Point posInit, Point spriteSize, float maxVelocity = 1)
    : GameObject(spriteFiles[0], posInit, spriteSize, maxVelocity) {
        for(auto& s : spriteFiles) {
            sprites.push_back(std::make_shared<Sprite>(s, posInit));
        }
    }

    std::shared_ptr<Sprite>& getSprite() {
        return sprites[currentSprite];
    }
};