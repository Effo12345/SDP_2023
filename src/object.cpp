#include "point.cpp"

/*
 * @author Ethan Rosati
 *
 * Base class that holds properties all on-screen objects must have
 * 
 * 
 * 
 */

class Object {
    Point pos;

    bool isActive = true;
    bool isDestroyed = false;

    public:
    virtual ~Object() {
        // Nothing to do since members can clean up after themselves
    }


    Point getPos() {
        return pos;
    }

    void setPos(int x, int y) {
        pos = {x, y};
    }

    void setPos(Point p) {
        pos = p;
    }

    void destroy() {
        isActive = false;
        isDestroyed = false;
    }

    virtual void draw() {

    }


};

int main() {

}