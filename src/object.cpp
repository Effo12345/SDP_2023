#include "include/object.hpp"


Object::~Object() {
    // Nothing to do since members can clean up after themselves
    // but necessary for derived classes
}

// Returns the object's position
Point Object::getPos() {
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
    isActive = false;
    isDestroyed = true;
}

// Let derived classes override this for draw calls in the render queue
void Object::draw() {}