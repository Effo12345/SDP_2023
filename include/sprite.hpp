#pragma once

#include "object.hpp"
#include "FEHImages.h"

class Sprite : public Object, public FEHImage {
    public:
    Sprite(std::string file) {
        Open(file.c_str());
    }

    Sprite(std::string file, int initX, int initY)
    : Sprite(file) {
        pos.x = initX;
        pos.y = initY;
    }

    Sprite(std::string file, Point initPos) 
    : Sprite(file, initPos.x, initPos.y) {}
    

    ~Sprite() {
        Close();
    }

    void draw() {
        Draw(pos.x, pos.y);
    }

};