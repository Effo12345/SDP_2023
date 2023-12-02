#include "include/boat.hpp"

void Boat::updateSpriteAngle() {
    Point delta = gamePos - targetPos;
    delta.normalize();

    if(fabs(delta.y) >= fabs(delta.x)) {
        isVertical = true;

        if(delta.y > 0) {
            // up
            currentSprite = 0;
        }
        else if(delta.y < 0) {
            // down
            currentSprite = 2;
        }
    }
    else {
        isVertical = false;

        if(delta.x > 0) {
            // left
            currentSprite = 3;
        }
        else if(delta.x < 0) {
            // right
            currentSprite = 1;
        }
    }

    if(isVertical != wasVertical) {
        spriteSize.transpose();
    }

    wasVertical = isVertical;
}

Boat::Boat(std::vector<std::string> spriteFiles, Point startingPos, Point spriteDim, float maxVel) 
: GameObject(startingPos, maxVel), spriteSize(spriteDim) {
    for(auto& str : spriteFiles) {
        sprites.push_back(
            std::make_shared<Sprite>(str, startingPos - (spriteDim / 2))
        );
    }
}

bool Boat::isColliding(Point objPos) {
    Point delta = gamePos - objPos;

    if(fabs(delta.x) < (spriteSize.x / 2) && fabs(delta.y) < (spriteSize.y / 2))
        return true;
    else
        return false;
}

void Boat::setTarget(Point touch) {
    GameObject::setTarget(touch);

    updateSpriteAngle();
}


void Boat::draw() {
    Point renderPos = gamePos - (spriteSize / 2);

    for(auto& p : sprites) {
        p->setPos(renderPos);
    }

    sprites[currentSprite]->draw();

    if(debugMode) {
        LCD.DrawRectangle(renderPos.x, renderPos.y, spriteSize.x, spriteSize.y);
    }
}
