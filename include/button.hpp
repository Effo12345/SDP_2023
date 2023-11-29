#pragma once
#include "point.hpp"

class Button {
    Point pos;
    Point size;

    bool isActive = false;

public:
    Button(Point position, Point dim)
    : pos{position}, size{dim} {}

    bool poll(Point touchPos) {
        if(!isActive)
            return false;

        if(touchPos > pos && touchPos < pos + size)
            return true;
        else
            return false;
    }

    void setActive(bool active = true) {
        isActive = active;
    }

    bool getActive() const {
        return isActive;
    }
};