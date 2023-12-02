#include "include/turtle.hpp"

Turtle::Turtle(Point startingPos, Point spriteDim, int maxVel) 
: GameObject(startingPos, maxVel), spriteSize{spriteDim} {
    staticSprite = std::make_shared<Sprite>(turtleFilepath + "static.pic", startingPos - (spriteDim / 2));

    for(int i = 0; i < numTurtleSprites; i++) {
        std::string file = turtleFilepath + std::to_string(i + 1) + ".pic";
        animSprites[i] = std::make_shared<Sprite>(file, startingPos - (spriteDim / 2));
    }
}

void Turtle::draw() {
    Point renderPos = gamePos - (spriteSize / 2);

    if(hasReachedTarget()) {
        staticSprite->setPos(renderPos);
        staticSprite->draw();
        return;
    }

    
    animIter++;

    if(animIter > numTurtleSprites - 1) {
        animIter = 0;
    }

    animSprites[animIter]->setPos(renderPos);
    animSprites[animIter]->draw();
}
