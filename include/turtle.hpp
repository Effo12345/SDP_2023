#pragma once

#include "renderobject.hpp"
#include "gameobject.hpp"
#include <array>

/**
 * @author Ethan Rosati
 * 
 * Implements the behavior of the turtles as both stationary and mobile
 * gameobjects. Handles motion and rendering using inherited classes
 **/
class Turtle : public RenderObject, public GameObject {
    // The number of sprites within the turtle's walk cycle
    const static int numTurtleSprites = 4;
    // Filepath to turtle sprites
    std::string turtleFilepath = "images/turtle/";
    Point spriteSize;

    // Track the current animation index
    int animIter {};

    // Sprite to use while the turtle is on the beach
    std::shared_ptr<Sprite> staticSprite;
    // Sprite to use when the turtle swims out to sea
    std::array<std::shared_ptr<Sprite>, numTurtleSprites> animSprites;

public:
    Turtle(Point startingPos, Point spriteDim, int maxVel);

    void draw();  
};
