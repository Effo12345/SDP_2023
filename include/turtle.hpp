#pragma once

#include "renderobject.hpp"
#include "gameobject.hpp"
#include <array>

class Turtle : public RenderObject, public GameObject {
const static int numTurtleSprites = 6;
std::string turtleFilepath = "images/turtle/";
Point spriteSize;
int animIter {};

std::array<std::shared_ptr<Sprite>, numTurtleSprites> sprites;

public:
    Turtle(Point startingPos, Point spriteDim, int maxVel);

    void draw();
    
};
