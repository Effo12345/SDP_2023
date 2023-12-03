#pragma once

#include "renderobject.hpp"
#include "FEHImages.h"

/**
 * @author Ethan Rosati
 * 
 * Wrapper class to encapsulate the functionality of FEHImage. Holds position 
 * data by inheriting from RenderObject and can be placed directly on the render
 * queue.
 **/
class Sprite : public RenderObject, public FEHImage {

public:
    Sprite(std::string file);
    Sprite(std::string file, int initX, int initY);
    Sprite(std::string file, Point initPos);
    
    ~Sprite();

    void draw();
};