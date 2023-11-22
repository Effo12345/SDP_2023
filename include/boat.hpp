#pragma once

#include "gameobject.hpp"
#include <vector>
#include <array>
#include <float.h>

class Boat : public RenderObject, public GameObject {
    std::vector<std::shared_ptr<Sprite>> sprites;
    int currentSprite {};
    Point spriteSize;

    void updateSpriteAngle() {
        Point delta = gamePos - targetPos;
        delta.normalize();

        if(fabs(delta.y) >= fabs(delta.x)) {
            if(delta.y > 0) {
                // up
                currentSprite = 0;
            }
            else if(delta.y < 0) {
                // down
                currentSprite = 2;
            }
        }
        else {
            if(delta.x > 0) {
                // left
                currentSprite = 3;
            }
            else if(delta.x < 0) {
                // right
                currentSprite = 1;
            }
        }
    }


public:
    Boat(std::vector<std::string> spriteFiles, Point startingPos, Point spriteDim, float maxVel = 1) 
    : GameObject(startingPos, maxVel), spriteSize(spriteDim) {
        for(auto& str : spriteFiles) {
            sprites.push_back(
                std::make_shared<Sprite>(str, startingPos - (spriteDim / 2))
            );
        }
    }

    void setTarget(Point touch) {
        GameObject::setTarget(touch);

        updateSpriteAngle();
    }


    void draw() {
        for(auto& p : sprites) {
            p->setPos(gamePos - (spriteSize / 2));
        }

        sprites[currentSprite]->draw();
    }
};