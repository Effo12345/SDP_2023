#pragma once

#include "gameobject.hpp"
#include <vector>
#include <array>
#include <float.h>

class Boat : public RenderObject, public GameObject {
    std::vector<std::shared_ptr<Sprite>> sprites;
    int currentSprite {};
    Point spriteSize;

    bool isVertical = true;
    bool wasVertical = true;

    bool debugMode = false;

    void updateSpriteAngle();


public:
    Boat(std::vector<std::string> spriteFiles, Point startingPos, Point spriteDim, float maxVel = 1);

    bool isColliding(Point objPos);

    void setTarget(Point touch);


    void draw();
};