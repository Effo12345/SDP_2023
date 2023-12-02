#pragma once

#include "sprite.hpp"
#include <memory>
#include <iostream>

class GameObject {
    Point prevDeltaSgn;
    bool reachedTarget = true;
    
    float speed;

    // https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    Point computeNewPos(Point& currPos, Point& delta, Point& deltaSgn, int speed);
protected:
    float targetAngle {};
    Point gamePos;
    Point targetPos;


public:
    GameObject(Point posInit, float maxVelocity = 1);

    void moveTowards ();

    void setTarget(Point touchPos);

    Point getPos();

    bool hasReachedTarget();
};