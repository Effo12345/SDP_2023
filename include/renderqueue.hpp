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

    void removeDestroyed();

public:

    RenderQueue(std::vector<std::shared_ptr<RenderObject>> baseObjects);

    RenderQueue() {}
    
    ~RenderQueue();

    void draw();

    void appendObject(std::shared_ptr<RenderObject> obj);

    void removeObject(int index);

    void doUpdateLcd(bool doUpdate = true);

    std::shared_ptr<RenderObject>& operator[](int index) {
        return objects[index];
    }
    
};