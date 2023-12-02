#include "include/renderobject.hpp"


RenderObject::~RenderObject() {
    // Nothing to do since members can clean up after themselves
    // but necessary for derived classes
}

// Sets objects position. Overloaded
void RenderObject::setPos(int x, int y) {
    renderPos = {x, y};
}

// Another way of set the object's position. Overloaded
void RenderObject::setPos(Point p) {
    renderPos = p;
}

// Mark the object as having been destroyed
void RenderObject::destroy() {
    destroyed = true;
}

// Return the object's destroyed status
bool RenderObject::isDestroyed() const {
    return destroyed;
}

// Set whether the object is visible on screen
void RenderObject::setActive(bool status) {
    active = status;
}

// Return whether or not object is visible
bool RenderObject::isActive() const {
    return active;
}

// Let derived classes override this for draw calls in the render queue
void RenderObject::draw() {}