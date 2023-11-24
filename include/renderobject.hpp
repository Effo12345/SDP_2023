#pragma once

#include "point.hpp"
#include <iostream>

/*
 * @author Ethan Rosati
 *
 * Base class that holds properties all on-screen objects must have
 */
class RenderObject {
    private:
    bool active = true;
    bool destroyed = false;

    protected:
    Point renderPos;

    public:
    virtual ~RenderObject();

    // Returns the object's position
    //Point getPos() const;
    // Sets objects position. Overloaded
    void setPos(int x, int y);
    // Another way of set the object's position. Overloaded
    void setPos(Point p);

    // Mark the object as having been destroyed
    void destroy();
    bool isDestroyed() const;

    void setActive(bool status = true);
    bool isActive() const;

    // Let derived classes override this for draw calls in the render queue
    virtual void draw();
};