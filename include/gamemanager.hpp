#pragma once

#include "gameobject.hpp"
#include "renderqueue.hpp"
#include "FEHUtility.h"
#include <random>

class GameManager {
    Point initialBoatPos = {100, 100};

    std::shared_ptr<Sprite> bkg;
    std::shared_ptr<Boat> boat;

    int minSpawnCycles = 10;
    int maxSpawnCycles = 30;

    int minSpawnX = 10;
    int maxSpawnX = 300;

    int minTrashIndex = 0;
    int maxTrashIndex = 2;

    int dT = 50;

    std::vector<std::shared_ptr<GameObject>> trash;

    RenderQueue render;

public:
    GameManager(std::string bkgFile) {
        bkg = std::make_shared<Sprite>(bkgFile);
        boat = std::make_shared<Boat>(std::vector<std::string>{
            "images/BoatFEH.pic",
            "images/Boat_RightFEH.pic",
            "images/Boat_BottomFEH.pic",
            "images/Boat_LeftFEH.pic"
            }, initialBoatPos, Point(32, 35), 3);
    }

    ~GameManager() {
        bkg.reset();
        boat.reset();
    }

    void initialize() {
        render.appendObject(bkg);
        render.appendObject(boat);


        update();
    }

    void update() {
        int cyclesUntilSpawn {};

        std::random_device r;
        std::default_random_engine eng(r());
        std::uniform_int_distribution<int> spawnTime(minSpawnCycles, maxSpawnCycles);
        std::uniform_int_distribution<int> spawnLocation(minSpawnX, maxSpawnX);

        Point touchPos;

        while(true) {
            /*
            if(!cyclesUntilSpawn) {
                spawnTrash(spawnLocation(eng), trashSelector(eng));
                cyclesUntilSpawn = spawnTime(eng);
            }

            cyclesUntilSpawn--;

            for(auto& t : trash) {
                t->moveTowards();
            }

            std::cout << cyclesUntilSpawn << "\n";
            */

            if(LCD.Touch(&touchPos.x, &touchPos.y)) {
                boat->setTarget(touchPos);
            }

            if(!boat->hasReachedTarget()) {
                boat->moveTowards();
            }

            render.draw();


            Sleep(dT);
        }
    }

    /*
    void spawnTrash(int xSpawn) {
        std::shared_ptr<GameObject> tmp = std::make_shared<GameObject>("images/Boat_BottomFEH.pic", Point(xSpawn, 0), Point(32, 35), 2);
        trash.push_back(tmp);
        render.appendObject(tmp->getSprite());

            trashPiece->setTarget(Point(xSpawn, 200));

        }
    }
    */
};