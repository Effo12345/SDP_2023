#include "include/main.hpp"
#include "include/point.hpp"
#include "FEHUtility.h"
#include "include/gameobject.hpp"
#include "include/renderqueue.hpp"

int main()
{

    float currentTouchPosX;
    float currentTouchPosY;

    Point touchPos;

    std::shared_ptr<GameObject> boat = std::make_shared<GameObject>("images/BoatFEH.pic", Point(125, 32), Point(32, 35), 3);
    std::shared_ptr<Sprite> bkg = std::make_shared<Sprite>("images/SDP_BackgroundFEH.pic");
    RenderQueue render({bkg, boat->getSprite()});

    boat->setTarget(Point(125, 100));

    int numIter;
    while (1) {

        LCD.ClearBuffer();
        if (LCD.Touch(&currentTouchPosX, &currentTouchPosY)) {

            

        }

        boat->moveTowards();
        render.draw();

        numIter++;
        
        Sleep(100);
    }

    return 0;
}