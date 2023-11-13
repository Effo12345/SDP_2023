#pragma once

#include "point.hpp"

/*
 * @author Ethan Rosati
 *
 * Base class that holds properties all on-screen objects must have
 */
class Object {
    Point pos;

    bool isActive = true;
    bool destroyed = false;

    public:
    virtual ~Object() {
        // Nothing to do since members can clean up after themselves
        // but necessary for derived classes
    }

    // Returns the object's position
    Point getPos() {
        return pos;
    }

    // Sets objects position. Overloaded
    void setPos(int x, int y) {
        pos = {x, y};
    }

    // Another way of set the object's position. Overloaded
    void setPos(Point p) {
        pos = p;
    }

    // Mark the object as having been destroyed
    void destroy() {
        isActive = false;
        destroyed = true;
    }

    bool isDestroyed() {
        return destroyed;
    }

    // Let derived classes override this for draw calls in the render queue
    virtual void draw() {}
};