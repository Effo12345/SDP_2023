#pragma once

#include "gameobject.hpp"
#include <vector>
#include <array>
#include <float.h>

class Boat : public RenderObject, public GameObject {
    std::vector<std::shared_ptr<Sprite>> sprites;
    int currentSprite {};
    Point spriteSize;
    Point collisionBox;

    bool isVertical = true;
    bool wasVertical = true;

    bool debugMode = true;

    void updateSpriteAngle() {
        Point delta = gamePos - targetPos;
        delta.normalize();

        if(fabs(delta.y) >= fabs(delta.x)) {
            isVertical = true;

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
            isVertical = false;

            if(delta.x > 0) {
                // left
                currentSprite = 3;
            }
            else if(delta.x < 0) {
                // right
                currentSprite = 1;
            }
        }

        if(isVertical != wasVertical) {
            spriteSize.transpose();
        }

        wasVertical = isVertical;
    }


public:
    Boat(std::vector<std::string> spriteFiles, Point startingPos, Point spriteDim, Point collider, float maxVel = 1) 
    : GameObject(startingPos, maxVel), spriteSize(spriteDim), collisionBox(collider) {
        for(auto& str : spriteFiles) {
            sprites.push_back(
                std::make_shared<Sprite>(str, startingPos - (spriteDim / 2))
            );
        }

        std::cout << spriteSize.x << ", " << spriteSize.y << "\n";
    }

    bool isColliding(Point objPos) {
        Point delta = gamePos - objPos;

        if(fabs(delta.x) < (spriteSize.x / 2) && fabs(delta.y) < (spriteSize.y / 2))
            return true;
        else
            return false;
    }

    void setTarget(Point touch) {
        GameObject::setTarget(touch);

        updateSpriteAngle();
    }


    void draw() {
        Point renderPos = gamePos - (spriteSize / 2);

        for(auto& p : sprites) {
            p->setPos(renderPos);
        }

        sprites[currentSprite]->draw();

        if(debugMode) {
            LCD.DrawRectangle(renderPos.x, renderPos.y, spriteSize.x, spriteSize.y);
        }
    }
};