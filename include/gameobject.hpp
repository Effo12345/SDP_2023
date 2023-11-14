#pragma once

#include "sprite.hpp"

class GameObject : public Sprite {
    Point maxVel;
    Point targetVel;
    float targetAngle;
    
    int speed = 1;

public:
    GameObject(std::string spriteFile, Point posInit, int maxVelocity)
    : Sprite(spriteFile, posInit.x, posInit.y),
      speed(maxVelocity) {}

    void moveTowards (Point clickPos) {

        Point newPos = clickPos - pos;
        Point currentPos;

        if (newPos.x > 0 && newPos.y > 0) {

            currentPos = pos + speed;
            

            if (currentPos.x > clickPos.x) {

                currentPos.x -= clickPos.x;

            }

            if (currentPos.y > clickPos.y) {

                currentPos.y -= clickPos.y;

            }

            setPos(currentPos);
        }

    }

};