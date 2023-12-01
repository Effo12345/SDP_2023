#pragma once

#include <vector>
#include <memory>
#include "renderobject.hpp"
#include "FEHLCD.h"

/*
 * @author Ethan Rosati & Owen Chevalier
 *
 * Base class that holds properties all on-screen objects must have
 */

class RenderQueue {
    std::vector<std::shared_ptr<RenderObject>> objects;
    bool updateLcd = true;

    void removeDestroyed() {
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

    public:

    RenderQueue(std::vector<std::shared_ptr<RenderObject>> baseObjects)
    : objects(baseObjects) {}

    RenderQueue() {}
    
    ~RenderQueue() {
        for(auto p : objects) {
            // Clear memory
            p.reset();
        }
    }

    void draw() {
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

    void appendObject(std::shared_ptr<RenderObject> obj) {
        objects.push_back(obj);
    }

    void removeObject(int index) {
        objects.erase(objects.begin() + index);
    }

    void doUpdateLcd(bool doUpdate = true) {
        updateLcd = doUpdate;
    }

    std::shared_ptr<RenderObject>& operator[](int index) {
        return objects[index];
    }
    
};