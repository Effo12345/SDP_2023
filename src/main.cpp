#include "include/main.hpp"
#include "FEHUtility.h"
#include "include/gameobject.hpp"
#include "include/renderqueue.hpp"

int main()
{
    std::shared_ptr<GameObject> boat = std::make_shared<GameObject>("images/BoatFEH.pic", Point(150, 200), Point(1, 1));
    std::shared_ptr<Sprite> bkg = std::make_shared<Sprite>("images/SDP_BackgroundFEH.pic");
    RenderQueue render({bkg, boat});

    int numIter;
    while (1) {
        boat->moveTowards((Point(100, 100)));
        render.draw();

        numIter++;
        
        Sleep(100);
    }

    return 0;
}