#include "include/main.hpp"
#include "include/point.hpp"
#include "FEHUtility.h"
#include "FEHLCD.h"
#include "include/gameobject.hpp"
#include "include/renderqueue.hpp"

int main()
{

    bool touchSet = false;

    float mouseTouchX;
    float mouseTouchY;

    Point touchPos;

    std::shared_ptr<GameObject> boat = std::make_shared<GameObject>("images/BoatFEH.pic", Point(17, 111), Point(32, 35), 3);
    std::shared_ptr<Sprite> bkg = std::make_shared<Sprite>("images/SDP_BackgroundFEH.pic");
    RenderQueue render({bkg, boat->getSprite()});

    //boat->setTarget(Point(88, 12));

    while (1) {
        if(LCD.Touch(&touchPos.x, &touchPos.y)) {
            boat->setTarget(touchPos);
        }

        if(!boat->hasReachedTarget()) {
            boat->moveTowards();
        }

        //boat->moveTowards();
        render.draw();
        
        Sleep(50);
    }

    return 0;
}