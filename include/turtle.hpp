#pragma once

#include "renderobject.hpp"
#include "gameobject.hpp"
#include <array>

class Turtle : public RenderObject, public GameObject {
const static int numTurtleSprites = 4;
std::string turtleFilepath = "images/turtle/";
Point spriteSize;
int animIter {};

std::shared_ptr<Sprite> staticSprite;
std::array<std::shared_ptr<Sprite>, numTurtleSprites> animSprites;

public:
    Turtle(Point startingPos, Point spriteDim, int maxVel);

    void draw();
    
};
