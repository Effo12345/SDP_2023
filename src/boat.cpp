#include "include/boat.hpp"

/**
 * @author Ethan Rosati
 *
 * Constructs a new boat object, filling the sprite vector with sprites for all
 * orientations
 * 
 * @param spriteFiles Array of sprite filepaths in order (up, right, down, left)
 * @param startingPos Where the boat first appears on the screen
 * @param spriteDim The sprite's size in pixels
 * @param maxVel The boat's maximum allowable speed
 **/
Boat::Boat(std::vector<std::string> spriteFiles, Point startingPos, Point spriteDim, float maxVel) 
: GameObject(startingPos, maxVel), spriteSize(spriteDim) {
    // Fill the vector with all provided sprites
    for(auto& str : spriteFiles) {
        sprites.push_back(
            std::make_shared<Sprite>(str, startingPos - (spriteDim / 2))
        );
    }
}

/**
 * @author Ethan Rosati
 *
 * Updates member variable currentSprite to the correct sprite index depending 
 * on the direction from the boat's current position to its next target.
 **/
void Boat::updateSpriteAngle() {
    // delta = current - target (for sign reasons since screen top left is (0, 0))
    Point delta = gamePos - targetPos;
    // Normalize so x and y are on [0, 1]
    delta.normalize();

    // if the y component is larger...
    if(fabs(delta.y) >= fabs(delta.x)) {
        // ... the boat is moving vertically...
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
        // ... otherwise it's moving horizontally
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

    // If the boat changes between vertical and horizontal, change the orientation
    // of the render position and hitbox
    if(isVertical != wasVertical) {
        spriteSize.transpose();
    }

    // Update boolean flags for next call
    wasVertical = isVertical;
}

/**
 * @author Ethan Rosati
 *
 * Checks if the boat is colliding with an object at the given point. Depends
 * on a member variable tracking the size of the boat's hitbox
 * 
 * @param objPos Position to check against for collision
 * @return Whether the objects are colliding
 **/
bool Boat::isColliding(Point objPos) {
    // Gets discrete x and y distances between boat and object
    Point delta = gamePos - objPos;

    // Collision only if the object is within the boat's rectangular hitbox
    if(fabs(delta.x) < (spriteSize.x / 2) && fabs(delta.y) < (spriteSize.y / 2))
        return true;
    else
        return false;
}

/**
 * @author Ethan Rosati
 * 
 * Sets the boat's target for the next time moveTowards is called
 * 
 * @param touch New target position
 **/
void Boat::setTarget(Point touch) {
    // Call the base class' implementation of this function
    GameObject::setTarget(touch);

    updateSpriteAngle();
}

/**
 * @author Ethan Rosati
 * 
 * Draw the boat on screen. This function overrides the virtual function in the
 * base RenderObject class to be called by the render queue
 **/
void Boat::draw() {
    // gamePos gives the boat's center but the sprite is drawn from its top left 
    // corner. Transform between these two using the sprite size
    Point renderPos = gamePos - (spriteSize / 2);

    // Set the position of all sprites so there are no visual errors when
    // switching between them rapidly
    for(auto& p : sprites) {
        p->setPos(renderPos);
    }

    // Draw only the currently active sprite to the screen
    sprites[currentSprite]->draw();

    // Draw the boat's rectangular hitbox to debug object collisions
    if(debugMode) {
        LCD.DrawRectangle(renderPos.x, renderPos.y, spriteSize.x, spriteSize.y);
    }
}
