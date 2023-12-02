#pragma once
#include "point.hpp"

class Button {
    Point pos;
    Point size;

    bool isActive = true;

public:
    Button(Point position, Point dim);

    bool poll(Point touchPos);

    void setActive(bool active = true);

    bool getActive() const;
};