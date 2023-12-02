#include "include/turtle.hpp"

Turtle::Turtle(Point startingPos, Point spriteDim, int maxVel) 
: GameObject(startingPos, maxVel), spriteSize{spriteDim} {
    for(int i = 0; i < numTurtleSprites; i++) {
        std::string file = turtleFilepath + std::to_string(i + 1) + ".pic";
        sprites[i] = std::make_shared<Sprite>(file, startingPos - (spriteDim / 2));
    }
}

void Turtle::draw() {
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
