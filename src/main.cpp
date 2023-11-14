#include "include/main.hpp"
#include "FEHLCD.h"
#include "include/sprite.hpp"
#include "include/renderqueue.hpp"

int main()
{
    std::shared_ptr<Sprite> boat = std::make_shared<Sprite>("images/BoatFEH.pic");
    std::shared_ptr<Sprite> bkg = std::make_shared<Sprite>("images/SDP_BackgroundFEH.pic");
    RenderQueue render({bkg, boat});

    int numIter;
    while (1) {
        render.draw();

        if(numIter == 100) {
            boat->destroy();
            boat.reset();
        }

        //LCD.WriteLine(std::to_string(numIter));
        //LCD.Update();

        numIter++;
    }

    return 0;
}