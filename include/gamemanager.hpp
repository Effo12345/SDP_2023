#pragma once

#include "gameobject.hpp"
#include "renderqueue.hpp"
#include "FEHUtility.h"
#include "trash.hpp"
#include <random>
#include <algorithm>
#include "soundmanager.hpp"

class GameManager {
    Point initialBoatPos = {160, 130};

    std::shared_ptr<Sprite> bkg;
    std::shared_ptr<Boat> boat;
    std::shared_ptr<Sprite> target;
    std::vector<std::shared_ptr<Sprite>> turtles;

    SoundManager soundManager;

    int numLives = 3;
    int turtleXPose = 135;
    int turtleYPose = 185;
    int turtleSpacing = 20;

    Point targetSize {16, 16};

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

    void killTurtle() {
        turtles[turtles.size() - 1]->destroy();
        turtles.pop_back();
    }

public:
    GameManager(std::string bkgFile, int minTrashTime, int maxTrashTime, int timeStep = 50)
    : minSpawnCycles{minTrashTime}, maxSpawnCycles{maxTrashTime}, dT{timeStep} {
        bkg = std::make_shared<Sprite>(bkgFile);
        boat = std::make_shared<Boat>(std::vector<std::string>{
            "images/boat/up.pic",
            "images/boat/right.pic",
            "images/boat/down.pic",
            "images/boat/left.pic"
        }, initialBoatPos, Point(32, 35), Point(20, 25), 4);

        target = std::make_shared<Sprite>("images/trash0/full.pic");
        target->setActive(false);

        for(int i = 0; i < numLives; i++) {
            turtles.push_back(
                std::make_shared<Sprite>("images/turtle.pic", Point(turtleXPose + turtleSpacing * i, turtleYPose))
            );
        }
    }

    ~GameManager() {
        bkg.reset();
        boat.reset();
    }

    void initialize() {
        render.appendObject(bkg);
        render.appendObject(target);
        render.appendObject(boat);

        for(auto& sprite : turtles)
            render.appendObject(sprite);

        soundManager.BasePath = "sounds";

        update();
    }

    void update() {
        int cyclesUntilSpawn {};

        std::random_device r;
        std::default_random_engine eng(r());
        std::uniform_int_distribution<int> spawnTime(minSpawnCycles, maxSpawnCycles);
        std::uniform_int_distribution<int> spawnLocation(minSpawnX, maxSpawnX);
        std::uniform_int_distribution<int> trashIndex(minTrashIndex, maxTrashIndex);

        Point touchPos = initialBoatPos;

        while(true) {
            if(!cyclesUntilSpawn) {
                spawnTrash(spawnLocation(eng), trashIndex(eng));
                cyclesUntilSpawn = spawnTime(eng);
            }

            cyclesUntilSpawn--;

            for(int i = 0; i < trash.size();) {
                if(!trash[i]->hasReachedTarget()) {
                    trash[i]->moveTowards();
                    i++;
                }
                else {
                    trash.erase(trash.begin() + i);
                    killTurtle();
                    numLives--;
                }
            }

            if(numLives < 1) {
                break;
            }
            

            if(LCD.Touch(&touchPos.x, &touchPos.y)) {
                boundsCheckTouch(touchPos);
                boat->setTarget(touchPos);
                target->setPos(touchPos - (targetSize / 2));
            }

            if(!boat->hasReachedTarget()) {
                boat->moveTowards();
                target->setActive(true);
            }

            checkTrashCollision();

            render.draw();


            Sleep(dT);
        }
    }
};