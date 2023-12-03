#include "include/gameobject.hpp"

/**
 * @author Ethan Rosati
 * 
 * Constructs a new GameObject instance using an initializer list
 * 
 * @param posInit Object's starting position
 * @param maxVelocity Object's maximum allowable speed
 **/
GameObject::GameObject(Point posInit, float maxVelocity)
: speed(maxVelocity), gamePos(posInit),
    targetPos(gamePos) {}

/**
 * @author Ethan Rosati 
 * @author Sidar via StackExchange
 * @cite https://gamedev.stackexchange.com/a/48191
 * 
 * Calculates an object's new position for the next update. Passes point values
 * by reference to save memory but only modifes delta and deltaSgn
 * 
 * @param currPos Object's current coordinate
 * @param delta Difference between object's current and target positions
 * @param deltaSgn Sign of x- and y-values of delta. Modified by reference
 * @param speed Maximum overall speed of the object
 **/
Point GameObject::computeNewPos(const Point& currPos, Point& delta, Point& deltaSgn, int speed) {
    // Compute the sign of the delta between target and current
    // Used by caller to check proximity to target
    deltaSgn = {sgn(delta.x), sgn(delta.y)};
    
    // If the object has reached its target, set a flag and return
    if(delta == 0) {
        reachedTarget = true;
        return currPos;
    }

    // Make delta vector components on [0, 1]
    delta.normalize();
    
    // Split speed between x- and y-components to get displacement per update
    // Add to current position to place the displacement vector correctly
    return (delta * speed) + currPos;
}


/**
 * @author Ethan Rosati
 * 
 * Move the object from its current position towards its target position (as 
 * set by member variables)
 **/
void GameObject::moveTowards () {
    // Calculate difference between target and current, then get pos for next
    // update
    Point currDelta = targetPos - gamePos;
    Point currDeltaSgn; // Modified by reference in computeNewPos
    Point nextPos = computeNewPos(gamePos, currDelta, currDeltaSgn, speed);

    // Repeate the process to calculate the position two frames into the future
    Point nextDelta = targetPos - nextPos;
    Point nextDeltaSgn;
    Point futurePos = computeNewPos(nextPos, nextDelta, nextDeltaSgn, speed);

    // If the object would pass its target if it continued moving after the next
    // frame, snap the object to its target this frame. 
    if(!(currDeltaSgn == nextDeltaSgn)) {
        gamePos = targetPos;
        return;
    }
    
    // Set object's position for the next frame
    gamePos = nextPos;
}

/**
 * @author Ethan Rosati
 * 
 * Set the target the object is to move towards and fill member variables with
 * default values
 * 
 * @param touchPos New target
 **/
void GameObject::setTarget(Point touchPos) { 
    targetPos = touchPos;
    reachedTarget = false;
}

/**
 * @author Ethan Rosati
 * 
 * Const getter
 * 
 * @return current position
 **/
Point GameObject::getPos() const {
    return gamePos;
}

/**
 * @author Ethan Rosati
 * 
 * @return Whether object has reached its target position
 **/
bool GameObject::hasReachedTarget() {
    return reachedTarget;
}