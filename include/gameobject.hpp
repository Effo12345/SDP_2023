#pragma once

#include "sprite.hpp"
#include <memory>
#include <iostream>

/**
 * @author Ethan Rosati
 * 
 * Implements functions and attributes shared by all moving on-screen objects;
 * designed to be a base class inherited from by more specific implementations.
 * Calculates object movement using vector arithmetic
 */
class GameObject {
    bool reachedTarget = true;
    float speed;

    /**
     * @author user79758 via StackOverflow
     * @cite https://stackoverflow.com/a/4609795
     * 
     * Helper function that returns the sign of the parameter. 
     * Template function designed to work for any fundamental type.
     * 
     * @param val Value to check against
     * @return Integer sign of val (either -1, 0, or 1)
     **/
    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    Point computeNewPos(const Point& currPos, Point& delta, Point& deltaSgn, int speed);

protected:
    // Allow inherited classes access to these necessary values without exposing
    // them to the user
    Point gamePos;
    Point targetPos;

public:
    GameObject(Point posInit, float maxVelocity = 1);

    void moveTowards ();
    void setTarget(Point touchPos);

    Point getPos() const;
    bool hasReachedTarget();
};