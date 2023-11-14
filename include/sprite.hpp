#pragma once

#include "object.hpp"
#include "FEHImages.h"

class Sprite : public Object, public FEHImage {
    public:
    Sprite(std::string file) {
        Open(file.c_str());
    }

    ~Sprite() {
        Close();
    }

    void draw() {
        Draw(pos.x, pos.y);
    }

};