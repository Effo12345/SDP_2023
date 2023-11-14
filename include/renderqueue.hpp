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
        for(int i = 0; i < objects.size(); i++) {
            if(objects[i]->isDestroyed()) {
                removeObject(i);
                i--;
                continue;
            }
        }
    }

    public:

    RenderQueue(std::vector<std::shared_ptr<Object>> baseObjects)
    : objects{baseObjects} {}
    
    ~RenderQueue() {
        for(auto p : objects) {
            // Clear memory
            p.reset();
        }
    }

    void draw() {
        removeDestroyed();

        for(auto p : objects) {
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