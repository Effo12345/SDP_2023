#pragma once

#include "gameobject.hpp"
#include "renderqueue.hpp"
#include "FEHUtility.h"
#include "trash.hpp"
#include <random>
#include <algorithm>

class GameManager {
    Point initialBoatPos = {100, 100};

    std::shared_ptr<Sprite> bkg;
    std::shared_ptr<Boat> boat;

    Point minTouch{20, 20};
    Point maxTouch{299, 150};

    int minSpawnCycles = 10;
    int maxSpawnCycles = 30;

    int minSpawnX = 10;
    int maxSpawnX = 300;

    int minTrashIndex = 0;
    int maxTrashIndex = 3;

    int dT = 50;

    std::vector<std::shared_ptr<Trash>> trash;

    RenderQueue render;

    void spawnTrash(int xSpawn, int trashIndex) {
        std::shared_ptr<Trash> tmp = std::make_shared<Trash>(Point(xSpawn, 0), trashIndex);
        trash.push_back(tmp);
        render.appendObject(tmp);
    }

    void checkTrashCollision() {
        for(int i = 0; i < trash.size();) {
            if(boat->isColliding(trash[i]->getPos())) {
                trash[i]->destroy();
                trash.erase(trash.begin() + i);
                continue;
            }

            i++;
        }
    }

    void boundsCheckTouch(Point& touchPos) {
        touchPos.x = std::clamp(touchPos.x, minTouch.x, maxTouch.x);
        touchPos.y = std::clamp(touchPos.y, minTouch.y, maxTouch.y);
    }

public:
    GameManager(std::string bkgFile) {
        bkg = std::make_shared<Sprite>(bkgFile);
        boat = std::make_shared<Boat>(std::vector<std::string>{
            "images/boat/up.pic",
            "images/boat/right.pic",
            "images/boat/down.pic",
            "images/boat/left.pic"
        }, initialBoatPos, Point(32, 35), Point(20, 25), 3);
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
        std::uniform_int_distribution<int> trashIndex(minTrashIndex, maxTrashIndex);

        Point touchPos;

        while(true) {
            if(!cyclesUntilSpawn) {
                spawnTrash(spawnLocation(eng), trashIndex(eng));
                cyclesUntilSpawn = spawnTime(eng);
            }

            cyclesUntilSpawn--;

            for(auto& t : trash) {
                if(!t->hasReachedTarget())
                    t->moveTowards();
            }
            

            if(LCD.Touch(&touchPos.x, &touchPos.y)) {
                boundsCheckTouch(touchPos);
                boat->setTarget(touchPos);
            }

            if(!boat->hasReachedTarget()) {
                boat->moveTowards();
            }

            checkTrashCollision();

            render.draw();


            Sleep(dT);
        }
    }
};