#include "include/gameobject.hpp"

Point GameObject::computeNewPos(Point& currPos, Point& delta, Point& deltaSgn, int speed) {
    deltaSgn = {sgn(delta.x), sgn(delta.y)};

    if(delta == 0) {
        reachedTarget = true;
        return currPos;
    }

    //https://gamedev.stackexchange.com/questions/48119/how-do-i-calculate-how-an-object-will-move-from-one-point-to-another
    delta.normalize();
    
    return (delta * speed) + currPos;
}


GameObject::GameObject(Point posInit, float maxVelocity)
: speed(maxVelocity), gamePos(posInit),
    targetPos(gamePos) {}

void GameObject::moveTowards () {
    Point currDelta = targetPos - gamePos;
    Point currDeltaSgn; // Modified by reference in computeNewPos
    Point nextPos = computeNewPos(gamePos, currDelta, currDeltaSgn, speed);

    Point nextDelta = targetPos - nextPos;
    Point nextDeltaSgn;
    Point futurePos = computeNewPos(nextPos, nextDelta, nextDeltaSgn, speed);

    
    if(!(currDeltaSgn == nextDeltaSgn)) {
        gamePos = targetPos;
        return;
    }
    
    gamePos = nextPos;
}

void GameObject::setTarget(Point touchPos) { 
    targetPos = touchPos;

    Point delta = targetPos - gamePos;
    prevDeltaSgn = {sgn(delta.x), sgn(delta.y)};

    reachedTarget = false;
}

Point GameObject::getPos() {
    return gamePos;
}

bool GameObject::hasReachedTarget() {
    return reachedTarget;
}