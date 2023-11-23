#pragma once

#include "gameobject.hpp"
#include "renderqueue.hpp"
#include "FEHUtility.h"
#include "trash.hpp"
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
    int maxTrashIndex = 1;

    int dT = 50;

    std::vector<std::shared_ptr<Trash>> trash;

    RenderQueue render;

public:
    GameManager(std::string bkgFile) {
        bkg = std::make_shared<Sprite>(bkgFile);
        boat = std::make_shared<Boat>(std::vector<std::string>{
            "images/boat/up.pic",
            "images/boat/right.pic",
            "images/boat/down.pic",
            "images/boat/left.pic"
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
        std::uniform_int_distribution<int> trashIndex(minTrashIndex, maxTrashIndex);

        Point touchPos;

        while(true) {
            if(!cyclesUntilSpawn) {
                spawnTrash(spawnLocation(eng), trashIndex(eng));
                cyclesUntilSpawn = spawnTime(eng);
            }

            cyclesUntilSpawn--;

            for(auto& t : trash) {
                t->moveTowards();
            }

            //std::cout << cyclesUntilSpawn << "\n";
            

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

    void spawnTrash(int xSpawn, int trashIndex) {
        std::shared_ptr<Trash> tmp = std::make_shared<Trash>(Point(xSpawn, 0), trashIndex);
        trash.push_back(tmp);
        render.appendObject(tmp);

        //tmp->setTarget(Point(xSpawn, 200));
    }
};