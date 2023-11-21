#pragma once

#include "sprite.hpp"
#include <memory>
#include <iostream>

class GameObject {
    Point targetPos;
    Point prevDeltaSgn;
    bool reachedTarget = false;
    
    float speed;

    // https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    Point computeNewPos(Point& currPos, Point& delta, Point& deltaSgn, int speed) {
        deltaSgn = {sgn(delta.x), sgn(delta.y)};

        if(delta == 0) {
            reachedTarget = true;
            return currPos;
        }

        //https://gamedev.stackexchange.com/questions/48119/how-do-i-calculate-how-an-object-will-move-from-one-point-to-another
        delta.normalize();
        
        return (delta * speed) + currPos;
    }

    void computeTargetAngle(Point delta) {
        targetAngle = acos(delta.x / sqrt((pow(delta.x, 2) + pow(delta.y, 2))));

        /*
        if(delta.y > 0) {
            targetAngle *= -1;
        }
        */
    }

    virtual void updateSprite() {}

protected:
    float targetAngle {};
    Point gamePos;
    Point spriteDim;
    std::shared_ptr<Sprite> sprite;


public:
    GameObject(std::string spriteFile, Point posInit, Point spriteSize, float maxVelocity = 1)
    : sprite(std::make_shared<Sprite>(spriteFile, Point(posInit.x, posInit.y) - spriteSize)),
      speed(maxVelocity), spriteDim(spriteSize), gamePos({posInit.x, posInit.y}),
      targetPos(gamePos) {
    }

    void moveTowards () {
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
        updateSprite();
    }

    void setTarget(Point touchPos) { 
        targetPos = touchPos;

        Point delta = targetPos - gamePos;
        prevDeltaSgn = {sgn(delta.x), sgn(delta.y)};

        computeTargetAngle(delta);

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