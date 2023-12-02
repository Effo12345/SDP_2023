#include "include/renderqueue.hpp"

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


RenderQueue::RenderQueue(std::vector<std::shared_ptr<RenderObject>> baseObjects)
: objects(baseObjects) {}

RenderQueue::~RenderQueue() {
    for(auto p : objects) {
        // Clear memory
        p.reset();
    }
}

void RenderQueue::draw() {
    removeDestroyed();

    for(auto p : objects) {
        // If the object is inactive, don't render it to the screen
        if(!p->isActive())
            continue;

        p->draw();
    }

    if(updateLcd)
        LCD.Update();
}

void RenderQueue::appendObject(std::shared_ptr<RenderObject> obj) {
    objects.push_back(obj);
}

void RenderQueue::removeObject(int index) {
    objects.erase(objects.begin() + index);
}

void RenderQueue::doUpdateLcd(bool doUpdate) {
    updateLcd = doUpdate;
}

    