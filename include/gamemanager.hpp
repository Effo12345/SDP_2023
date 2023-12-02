#pragma once

#include "gameobject.hpp"
#include "renderqueue.hpp"
#include "FEHUtility.h"
#include "trash.hpp"
#include <random>
#include <algorithm>
#include "soundmanager.hpp"
#include "stats.hpp"
#include "turtle.hpp"
#include "button.hpp"

class GameManager {
    Point initialBoatPos = {160, 130};

    std::shared_ptr<Sprite> bkg;
    std::shared_ptr<Boat> boat;
    std::shared_ptr<Sprite> target;
    std::vector<std::shared_ptr<Turtle>> turtles;
    std::shared_ptr<Sprite> failScreen;

    SoundManager soundManager;
    std::string musicPath;
    
    bool &completedLevel;
    bool &exitToMenu;

    int numLives = 3;
    int turtleXPose = 135;
    int turtleYPose = 185;
    int turtleSpacing = 20;
    int turtleTargetY = 10;

    Point targetSize {16, 16};

    Point minTouch{20, 20};
    Point maxTouch{299, 150};

    int minSpawnCycles = 10;
    int maxSpawnCycles = 30;

    int minSpawnX = 10;
    int maxSpawnX = 300;

    int minTrashIndex = 0;
    int maxTrashIndex = 3;

    int minTurtleSpeed = 1;
    int maxTurtleSpeed = 3;

    int trashCollectionTarget {};
    int trashCollected {};

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

                trashCollected++;

                soundManager.play("pickupTrash.wav", 0.25f);
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

        soundManager.play("turtleDeath.wav", 1.0f);
    }

    void levelCompleted() {
        soundManager.stopSounds();
        Sleep(500);
        soundManager.play("savedTurtles.wav");

        // Remove all on-screen objects but turtles and background
        for(auto& t : trash)
            t->destroy();
        trash.clear();
        boat->destroy();
        target->destroy();

        for(auto& t : turtles)
            t->setTarget(Point(t->getPos().x, turtleTargetY));

        float animTime = 3.0f;  // seconds
        float startTime = TimeNow();
        while(TimeNow() - startTime < animTime) {
            for(auto& t : turtles)
                t->moveTowards();

            render.draw();
            Sleep(dT);
        }

        render.doUpdateLcd(false);

        for(int i = 0; i < 241; i += 6) {
            for(auto& t : turtles)
                t->moveTowards();

            render.draw();

            LCD.SetFontColor(BLACK);
            LCD.FillRectangle(0, 0, 320, i);
            LCD.Update();

            Sleep(1);
        }
        Sleep(100);

        completedLevel = true;
        exitToMenu = false;
    }

    void levelFailed() {
        soundManager.stopSounds();
        Sleep(500);
        soundManager.play("killedTurtles.wav");

        render.appendObject(failScreen);
        render.draw();

        Button replay {Point{116, 94}, Point{87, 23}};
        Button exit {Point{83, 133}, Point{152, 23}};
        Point touchPos;

        bool validInput = false;
        while(!validInput) {
            if(!LCD.Touch(&touchPos.x, &touchPos.y))
                continue;

            if(replay.poll(touchPos)) {
                exitToMenu = false;
                validInput = true;
            }
            else if(exit.poll(touchPos)) {
                exitToMenu = true;
                validInput = true;
            }

            Sleep(dT);
        }

        completedLevel = false;
        
    }

    void fillTurtleArray() {
        std::random_device r;
        std::default_random_engine eng(r());
        std::uniform_int_distribution<int> turtleSpeed(minTurtleSpeed, maxTurtleSpeed);

        for(int i = 0; i < numLives; i++) {
            turtles.push_back(std::make_shared<Turtle>
                (Point(turtleXPose + turtleSpacing * i, turtleYPose), Point(16, 16), turtleSpeed(eng))
            );
        }
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
                levelFailed();
                break;
            }

            if(trashCollected >= trashCollectionTarget) {
                levelCompleted();
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

public:
    GameManager(std::string bkgFile, std::string musicFile, std::string gameOverFile,
        bool &success, bool &quit, 
        int targetTrash, int minTrashTime, int maxTrashTime, int timeStep = 50)
    : musicPath{musicFile}, completedLevel{success}, exitToMenu{quit}, 
      trashCollectionTarget{targetTrash}, minSpawnCycles{minTrashTime}, maxSpawnCycles{maxTrashTime}, 
      dT{timeStep} {
        bkg = std::make_shared<Sprite>(bkgFile);
        boat = std::make_shared<Boat>(std::vector<std::string>{
            "images/boat/up.pic",
            "images/boat/right.pic",
            "images/boat/down.pic",
            "images/boat/left.pic"
        }, initialBoatPos, Point(32, 35), 4);

        target = std::make_shared<Sprite>("images/target.pic");
        target->setActive(false);

        failScreen = std::make_shared<Sprite>(gameOverFile, Point{0, 0});

        fillTurtleArray();
    }

    ~GameManager() {
        bkg.reset();
        boat.reset();
    }

    void initialize() {
        render.appendObject(bkg);
        render.appendObject(target);
        render.appendObject(boat);

        for(auto& turtle : turtles)
            render.appendObject(turtle);

        Sleep(100);

        soundManager.BasePath = "sounds";
        soundManager.play(musicPath.c_str(), 0.75f, true);

        LCD.ClearBuffer();

        update();
    }

    void updateStats(Stats& stats) {
        stats.trashCollected += trashCollected;
        stats.turtlesSaved += numLives;

        if(completedLevel) {
            stats.levelsCompleted++;
        }
    }
};