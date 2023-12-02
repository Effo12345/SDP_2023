#include "include/sprite.hpp"

Sprite::Sprite(std::string file) {
    Open(file.c_str());
}

Sprite::Sprite(std::string file, int initX, int initY)
: Sprite(file) {
    renderPos.x = initX;
    renderPos.y = initY;
}

Sprite::Sprite(std::string file, Point initPos) 
: Sprite(file, initPos.x, initPos.y) {}


Sprite::~Sprite() {
    Close();
}

void Sprite::draw() {
    Draw(std::round(renderPos.x), std::round(renderPos.y));
}