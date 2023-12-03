#pragma once

#include <vector>
#include <memory>
#include "renderobject.hpp"
#include "FEHLCD.h"

/**
 * @author Ethan Rosati
 * @author Owen Chevalier
 *
 * Renderer in charge of drawing all on-screen objects using the Proteus LCD.
 * Draws all polymorphic objects from a single array
 **/
class RenderQueue {
    // Array of objects to be drawn
    std::vector<std::shared_ptr<RenderObject>> objects;

    // Track whether the class is allowed to call LCD.Update()
    // If false, the caller is in charge of updating the LCD, so true by default
    bool updateLcd = true;

    void removeDestroyed();

public:
    RenderQueue(std::vector<std::shared_ptr<RenderObject>> baseObjects);
    // Default constructor
    RenderQueue() {}
    
    ~RenderQueue();

    void draw();

    void appendObject(std::shared_ptr<RenderObject> obj);
    void removeObject(int index);

    void doUpdateLcd(bool doUpdate = true);
};