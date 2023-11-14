#pragma once

#include "gameobject.hpp"
#include "renderqueue.hpp"

class GameManager {
    Point initialBoatPos = {0, 0};

    std::shared_ptr<Sprite> bkg;
    std::shared_ptr<GameObject> boat;

public:
    GameManager(std::string bkgFile, std::string boatFile) {
        bkg = std::make_shared<Sprite>(bkgFile);
        boat = std::make_shared<GameObject>(boatFile, initialBoatPos);
    }

    ~GameManager() {
        bkg.reset();
        boat.reset();
    }
};