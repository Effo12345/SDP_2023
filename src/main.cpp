#include "include/main.hpp"
#include "include/point.hpp"
#include "FEHUtility.h"
#include "FEHLCD.h"
#include "include/gameobject.hpp"
#include "include/renderqueue.hpp"
#include "include/boat.hpp"
#include "include/gamemanager.hpp"

int main() {
    /*
    bool touchSet = false;

    float mouseTouchX;
    float mouseTouchY;

    Point touchPos;

    std::shared_ptr<Boat> boat = std::make_shared<Boat>(std::vector<char*>{"images/Boat_RightFEH.pic", "images/BoatFEH.pic", "images/Boat_LeftFEH.pic", "images/Boat_BottomFEH.pic"}, Point(17, 111), Point(32, 35), 3);
    std::shared_ptr<Sprite> bkg = std::make_shared<Sprite>("images/SDP_BackgroundFEH.pic");
    RenderQueue render({bkg, boat->getSprite()});

    //boat->setTarget(Point(88, 12));

    while (1) {
        if(LCD.Touch(&touchPos.x, &touchPos.y)) {
            boat->setTarget(touchPos);
            render[1] = boat->getSprite();
        }

        if(!boat->hasReachedTarget()) {
            boat->moveTowards();
        }

        //boat->moveTowards();
        render.draw();
        
        Sleep(50);
    }
    */

   GameManager level1("images/SDP_BackgroundFEH.pic", "BoatFEH.pic");
   level1.initialize();

    return 0;
}