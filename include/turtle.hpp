#pragma once

#include "renderobject.hpp"
#include "gameobject.hpp"
#include <array>

class Turtle : public RenderObject, public GameObject {
const static int numTurtleSprites = 6;
std::string turtleFilepath = "images/turtle/";
Point spriteSize;
int animIter {};

std::array<std::shared_ptr<Sprite>, numTurtleSprites> sprites;

public:
    Turtle(Point startingPos, Point spriteDim, int maxVel) 
    : GameObject(startingPos, maxVel), spriteSize{spriteDim} {
        for(int i = 0; i < numTurtleSprites; i++) {
            std::string file = turtleFilepath + std::to_string(i + 1) + ".pic";
            sprites[i] = std::make_shared<Sprite>(file, startingPos - (spriteDim / 2));
        }
    }

    void draw() {
        Point renderPos = gamePos - (spriteSize / 2);

        if(hasReachedTarget()) {
            sprites[0]->setPos(renderPos);
            sprites[0]->draw();
            return;
        }

        
        animIter++;

        if(animIter > numTurtleSprites - 1) {
            animIter = 0;
        }

        sprites[animIter]->setPos(renderPos);
        sprites[animIter]->draw();
    }
    
};
