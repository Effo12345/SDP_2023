#include "include/renderobject.hpp"

/*
 * Nothing to do since members can clean up after themselves
 * but necessary for derived classes
 */
RenderObject::~RenderObject() {}

/**
 * @author Ethan Rosati
 * 
 * Sets the object's on-screen render position. Overloaded
 * 
 * @param x Object's x-position
 * @param y Object's y-position
 **/
void RenderObject::setPos(int x, int y) {
    renderPos = {x, y};
}

/**
 * @author Ethan Rosati
 * 
 * Another way to set the object's position. Overloaded
 * 
 * @param p Point containing x and y position data
 **/
void RenderObject::setPos(Point p) {
    renderPos = p;
}

/**
 * @author Ethan Rosati
 * 
 * Mark the object as having been destroyed so the caller knows not to render it
 **/
void RenderObject::destroy() {
    destroyed = true;
}

/**
 * @author Ethan Rosati
 * 
 * Const getter
 * 
 * @return Whether the object has been destroyed 
 **/
bool RenderObject::isDestroyed() const {
    return destroyed;
}

/**
 * @author Ethan Rosati
 * 
 * Sets whether the object is visible on-screen
 * 
 * @param status If the object should be visible. True by default 
 **/
void RenderObject::setActive(bool status) {
    active = status;
}

/**
 * @author Ethan Rosati
 * 
 * Const getter
 * 
 * @return Whether the object is currently visible
 **/
bool RenderObject::isActive() const {
    return active;
}

/**
 * Let derived classes override this for draw calls in the render queue
 **/
void RenderObject::draw() {}