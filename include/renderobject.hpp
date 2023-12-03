#pragma once

#include "point.hpp"
#include <iostream>

/**
 * @author Ethan Rosati
 *
 * Base class that holds properties all on-screen objects must have; designed to
 * be inherited from by more specific classes. Exposes virtual functions that
 * derived classes overwrite to be accessed polymorphically
 **/
class RenderObject {
private:
    // Track the current state of the object
    bool active = true;
    bool destroyed = false;

protected:
    // Provide access to derived classes without exposing to the user
    Point renderPos;

public:
    virtual ~RenderObject();

    void setPos(int x, int y);
    void setPos(Point p);

    void destroy();
    bool isDestroyed() const;

    void setActive(bool status = true);
    bool isActive() const;

    virtual void draw();
};