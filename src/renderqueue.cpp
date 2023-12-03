#include "include/renderqueue.hpp"

/**
 * @author Ethan Rosati
 * 
 * Constructs a new RenderObject class using an initializer list. Overloaded
 * with default constructor
 * 
 * @param baseobjects Objects to be placed at the bottom of the render queue
 **/
RenderQueue::RenderQueue(std::vector<std::shared_ptr<RenderObject>> baseObjects)
: objects(baseObjects) {}

/**
 * @author Ethan Rosati
 * 
 * Clear out the array of shared pointers so the memory their objets use goes
 * out of scope
 **/
RenderQueue::~RenderQueue() {
    for(auto p : objects) {
        // Clear memory
        p.reset();
    }
}

/**
 * @author Ethan Rosati
 * 
 * Calls the draw function for all objects in the object array. Must be called 
 * every frame.
 **/
void RenderQueue::draw() {
    removeDestroyed();

    for(auto p : objects) {
        // If the object is inactive, don't render it to the screen
        if(!p->isActive())
            continue;

        // Otherwise, call its draw function
        p->draw();
    }

    // Once all objects have been drawn, update the LCD if we have permission to
    if(updateLcd)
        LCD.Update();
}

/**
 * @author Ethan Rosati
 * @author Owen Chevalier
 * 
 * Removes from the object vector any objects that have been destroyed since the
 * previous updates. Destroyed objects are removed from memory and no longer 
 * drawn to the screen
 **/
void RenderQueue::removeDestroyed() {
    for(int i = 0; i < objects.size();) {
        if(objects[i]->isDestroyed()) {
            removeObject(i);
            continue;
        }

        // Only increment the iterator if the current object wasn't destroyed
        // since erasing an object from the vector pushes all the indeces up
        i++;
    }
}

/**
 * @author Ethan Rosati
 * 
 * Add a new object to the end of the render queue (so it is drawn on top)
 * 
 * @param obj Object to be appended
 **/
void RenderQueue::appendObject(std::shared_ptr<RenderObject> obj) {
    objects.push_back(obj);
}

/**
 * @author Ethan Rosati
 * 
 * Remove an object from the render queue so that it is no longer drawn or
 * tracked
 * 
 * @param index Index of the object array to be erased
 **/
void RenderQueue::removeObject(int index) {
    objects.erase(objects.begin() + index);
}

/**
 * @author Ethan Rosati
 * 
 * Set whether the class is allowed to call LCD.Update() during the draw
 * function.
 * 
 * @param doUpdate Allow update call or not. True by default
 **/
void RenderQueue::doUpdateLcd(bool doUpdate) {
    updateLcd = doUpdate;
}

    