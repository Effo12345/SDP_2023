#pragma once

#include <vector>
#include <memory>
#include "object.hpp"
#include "FEHLCD.h"

/*
 * @author Ethan Rosati & Owen Chevalier
 *
 * Base class that holds properties all on-screen objects must have
 */

class RenderQueue {
    std::vector<std::shared_ptr<Object>> objects;

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

    RenderQueue(std::vector<std::shared_ptr<Object>> baseObjects)
    : objects(baseObjects) {}
    
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

        LCD.Update();
    }

    void appendObject(std::shared_ptr<Object> obj) {
        objects.push_back(obj);
    }

    void removeObject(int index) {
        objects.erase(objects.begin() + index);
    }
    
};