#include "include/sprite.hpp"

/**
 * @author Ethan Rosati
 * 
 * Construct a new Sprite object. Overloaded
 * 
 * @param file Filepath to the .pic file to be drawn
 **/
Sprite::Sprite(std::string file) {
    Open(file.c_str());
}

/**
 * @author Ethan Rosati
 * 
 * Construct a new Sprite object allowing for an initial position. Calls 
 * previous constructor in initializer list
 * 
 * @param file Filepath to the .pic file to be drawn
 * @param initX x-coordinate of sprite. Measured from top left of screen
 * @param initY y-coordinate of sprite. Measured from top left of screen
 **/
Sprite::Sprite(std::string file, int initX, int initY)
: Sprite(file) {
    renderPos.x = initX;
    renderPos.y = initY;
}

/**
 * @author Ethan Rosati
 * 
 * Construct a new Sprite object allowing for an initial position. Calls
 * previous constructor in initializer list
 * 
 * @param file Filepath to the .pic file to be drawn
 * @param initPos Coordinate of the sprite (both x and y)
 **/
Sprite::Sprite(std::string file, Point initPos) 
: Sprite(file, initPos.x, initPos.y) {}

/**
 * @author Ethan Rosati
 * 
 * Close the FEHImage once the Sprite is destroyed
 **/
Sprite::~Sprite() {
    Close();
}

/**
 * @author Ethan Rosati
 * 
 * Draw the Sprite to the screen using the Draw function inherited from
 * FEHImage. Round the sprite's position since Draw only takes integer values.
 **/
void Sprite::draw() {
    FEHImage::Draw(std::round(renderPos.x), std::round(renderPos.y));
}