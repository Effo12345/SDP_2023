#include "include/button.hpp"

Button::Button(Point position, Point dim)
: pos{position}, size{dim} {}

bool Button::poll(Point touchPos) {
    if(!isActive)
        return false;

    if(touchPos > pos && touchPos < pos + size)
        return true;
    else
        return false;
}

void Button::setActive(bool active) {
    isActive = active;
}

bool Button::getActive() const {
    return isActive;
}
