#pragma once
#include "point.hpp"

/**
 * @author Ethan Rosati
 * 
 * Custom button class to process touchscreen inputs into button presses. Member
 * variables track position, size, and activity to check against touch input.
 **/
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