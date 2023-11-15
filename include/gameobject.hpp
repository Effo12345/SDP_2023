#pragma once

#include "sprite.hpp"
#include <memory>
#include <iostream>

class GameObject {
    Point gamePos;
    Point spriteDim;
    std::shared_ptr<Sprite> sprite;

    Point targetPos;
    float targetAngle;
    Point prevDeltaSgn;
    bool reachedTarget = false;
    
    float speed;

    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }


public:
    GameObject(std::string spriteFile, Point posInit, Point spriteSize, float maxVelocity = 1)
    : sprite(std::make_shared<Sprite>(spriteFile, Point(posInit.x, posInit.y) - spriteSize)),
      speed(maxVelocity), spriteDim(spriteSize), gamePos({posInit.x, posInit.y}),
      targetPos(gamePos) {
    }

    Point computeNewPos(Point& currPos, Point& delta, Point& deltaSgn, int speed) {
        deltaSgn = {sgn(delta.x), sgn(delta.y)};

        if(delta == 0) {
            reachedTarget = true;
            return currPos;
        }

        delta.normalize();
        

        return (delta * speed) + currPos;
    }

    void moveTowards () {
        /*
        Point delta = targetPos - gamePos;
        Point deltaSgn = {sgn(delta.x), sgn(delta.y)};
        std::cout << "(" << delta.x << ", " << delta.y << ")\n";

        if(delta == 0) {
            return;
        }

        if(!(deltaSgn == prevDeltaSgn)) {
            setPos(targetPos);
            return;
        }

        float xPct = (float)delta.x / (float)(delta.x + delta.y);
        float yPct = (float)delta.y / (float)(delta.x + delta.y);

        std::cout << "(" << xPct << ", " << yPct << ")\n";

        Point vel = {std::round(xPct * speed * deltaSgn.x), std::round(yPct * speed * deltaSgn.y)};

        std::cout << "(" << vel.x << ", " << vel.y << ")\n\n";

        prevDeltaSgn = deltaSgn;

        setPos(gamePos + vel);
        */

        Point currDelta = targetPos - gamePos;
        Point currDeltaSgn; // Modified by reference in computeNewPos
        Point nextPos = computeNewPos(gamePos, currDelta, currDeltaSgn, speed);

        Point nextDelta = targetPos - nextPos;
        Point nextDeltaSgn;
        Point futurePos = computeNewPos(nextPos, nextDelta, nextDeltaSgn, speed);

        
        if(!(currDeltaSgn == nextDeltaSgn)) {
            setPos(targetPos);
            return;
        }
        

        setPos(nextPos);
    }

    void setTarget(Point touchPos) { 
        targetPos = touchPos;

        Point delta = targetPos - gamePos;
        prevDeltaSgn = {sgn(delta.x), sgn(delta.y)};

        reachedTarget = false;
    }

    void setPos(Point pos) {
        gamePos = pos;
        sprite->setPos(pos - (spriteDim / 2));
    }

    Point getPos() {
        return gamePos;
    }

    std::shared_ptr<Sprite> getSprite() {
        return sprite;
    }

    bool hasReachedTarget() {
        return reachedTarget;
    }
};