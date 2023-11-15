#pragma once

#include "renderobject.hpp"
#include "FEHImages.h"

class Sprite : public RenderObject, public FEHImage {
    public:
    Sprite(std::string file) {
        Open(file.c_str());
    }

    Sprite(std::string file, int initX, int initY)
    : Sprite(file) {
        renderPos.x = initX;
        renderPos.y = initY;
    }

    Sprite(std::string file, Point initPos) 
    : Sprite(file, initPos.x, initPos.y) {}
    

    ~Sprite() {
        Close();
    }

    void draw() {
        Draw(renderPos.x, renderPos.y);
    }

};