#include "include/turtle.hpp"

/**
 * @author Ethan Rosati
 * 
 * Constructs a new turtle object and handles filling its sprite arrays. Builds
 * inherited GameObject instance in an inizializer list
 * 
 * @param startingPos The turtle's starting position
 * @param spriteDim The size of the turtle sprite
 * @param maxVel The maximum permissable speed for the turtle to move per frame
 **/
Turtle::Turtle(Point startingPos, Point spriteDim, int maxVel) 
: GameObject(startingPos, maxVel), spriteSize{spriteDim} {
    // Fetch the sprite the turtle will use while on the beach
    // Offset its initial drawn position by the size of the sprite
    staticSprite = std::make_shared<Sprite>(turtleFilepath + "static.pic", startingPos - (spriteDim / 2));

    // Grab all frames of the turtle's walking animation and place them in an 
    // array for the end of the level
    for(int i = 0; i < numTurtleSprites; i++) {
        std::string file = turtleFilepath + std::to_string(i + 1) + ".pic";
        animSprites[i] = std::make_shared<Sprite>(file, startingPos - (spriteDim / 2));
    }
}

/**
 * @author Ethan Rosati
 * 
 * Draw the turtle onto the screen at its current position
 **/
void Turtle::draw() {
    // Offset the gamepos by the size of the sprite
    Point renderPos = gamePos - (spriteSize / 2);

    // If the turtle isn't moving, use its static sprite
    if(hasReachedTarget()) {
        staticSprite->setPos(renderPos);
        staticSprite->draw();
        return;
    }

    // If the turtle is moving, keep track of what animation frame to display...
    animIter++;

    // ... and ensure it keeps looping
    if(animIter > numTurtleSprites - 1) {
        animIter = 0;
    }

    // Draw the current frame of the turtle's animation
    animSprites[animIter]->setPos(renderPos);
    animSprites[animIter]->draw();
}
