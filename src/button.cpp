#include "include/button.hpp"

/**
 * @author Ethan Rosati
 * 
 * Constructs a new button object. Sets member variables for later use
 **/
Button::Button(Point position, Point dim)
: pos{position}, size{dim} {}

/**
 * @author Ethan Rosati
 * 
 * Poll whether the button is currently being pressed. Automatically returns
 * false if the button is set as inactive
 * 
 * @param touchPos Position to test against 
 * @return Whether the touch position is within the button's bounds
 **/
bool Button::poll(Point touchPos) {
    if(!isActive)
        return false;

    // Checks if both x- and y-coordinates are inside the button
    if(touchPos > pos && touchPos < pos + size)
        return true;
    else
        return false;
}

/**
 * @author Ethan Rosati
 * 
 * Sets whether the button accepts touch input. 
 * 
 * @param active Whether the button is active. True by default
 **/
void Button::setActive(bool active) {
    isActive = active;
}

/**
 * @author Ethan Rosati
 * 
 * Const getter
 * 
 * @return Whether button accepts touch input
 **/
bool Button::getActive() const {
    return isActive;
}
