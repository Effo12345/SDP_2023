#pragma once

#include "renderobject.hpp"
#include "FEHImages.h"

class Sprite : public RenderObject, public FEHImage {
    private:
        Point spriteSize;
    public:
    Sprite(std::string file);

    Sprite(std::string file, int initX, int initY);

    Sprite(std::string file, Point initPos);
    

    ~Sprite();

    void draw();
};