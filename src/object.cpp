#include "include/object.hpp"


Object::~Object() {
    // Nothing to do since members can clean up after themselves
    // but necessary for derived classes
}

// Returns the object's position
Point Object::getPos() const {
    return pos;
}

// Sets objects position. Overloaded
void Object::setPos(int x, int y) {
    pos = {x, y};
}

// Another way of set the object's position. Overloaded
void Object::setPos(Point p) {
    pos = p;
}

// Mark the object as having been destroyed
void Object::destroy() {
    destroyed = true;
}

// Return the object's destroyed status
bool Object::isDestroyed() const {
    return destroyed;
}

// Set whether the object is visible on screen
void Object::setActive(bool status) {
    active = status;
}

// Return whether or not object is visible
bool Object::isActive() const {
    return active;
}

// Let derived classes override this for draw calls in the render queue
void Object::draw() {}