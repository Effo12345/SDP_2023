#pragma once

#include "gameobject.hpp"
#include <vector>
#include <array>
#include <float.h>

/*
 * @author Ethan Rosati
 * 
 * Implements the functionality of the boat (the player character) in the game.
 * Inherits generalized methods from renderobject and gameobject, allowing 
 * direct placement onto the render queue. Member variables hold all sprites
 * necessary for the boat's 4 possible orietnations, an index to switch between
 * them, and size data to define the boat's rectangular hitbox.
 */
class Boat : public RenderObject, public GameObject {
    std::vector<std::shared_ptr<Sprite>> sprites;
    int currentSprite {};
    Point spriteSize;

    // Tracks boat orientation for sprite selection
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