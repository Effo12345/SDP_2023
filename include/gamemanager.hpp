#pragma once

#include "gameobject.hpp"
#include "renderqueue.hpp"
#include "FEHUtility.h"
#include <random>

class GameManager {
    Point initialBoatPos = {0, 0};

    std::shared_ptr<Sprite> bkg;
    std::shared_ptr<GameObject> boat;

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
    GameManager(std::string bkgFile, std::string boatFile) {
        bkg = std::make_shared<Sprite>(bkgFile);
        //boat = std::make_shared<GameObject>(boatFile, initialBoatPos, Point(0, 0), Point(32, 35), 3);
    }

    ~GameManager() {
        bkg.reset();
        boat.reset();
    }

    void initialize() {
        render.appendObject(bkg);
        //render.appendObject(boat->getSprite());


        update();
    }

    void update() {
        int cyclesUntilSpawn {};

        std::random_device r;
        std::default_random_engine eng(r());
        std::uniform_int_distribution<int> spawnTime(minSpawnCycles, maxSpawnCycles);
        std::uniform_int_distribution<int> spawnLocation(minSpawnX, maxSpawnX);
        std::uniform_int_distribution<int> trashSelector(minTrashIndex, maxTrashIndex);

        while(true) {
            if(!cyclesUntilSpawn) {
                spawnTrash(spawnLocation(eng), trashSelector(eng));
                cyclesUntilSpawn = spawnTime(eng);
            }
            
            cyclesUntilSpawn--;

            for(auto& t : trash) {
                t->moveTowards();
            }

            std::cout << cyclesUntilSpawn << "\n";
            

            render.draw();


            Sleep(dT);
        }
    }

    void spawnTrash(int xSpawn, int trashIndex) {

        std::shared_ptr<GameObject> trashPiece;

        if (trashIndex == 0) {

            trashPiece = std::make_shared<GameObject>("images/trash_piece_1/trash_piece_1_fullFEH.pic", Point(xSpawn, 0), Point(16, 16), 2);

            trash.push_back(trashPiece);
            render.appendObject(trashPiece->getSprite());

            trashPiece->setTarget(Point(xSpawn, 200));

        } else if (trashIndex == 1) {

            trashPiece = std::make_shared<GameObject>("images/trash_piece_3/trash_piece_3_fullFEH.pic", Point(xSpawn, 0), Point(16, 16), 2);
            
            trash.push_back(trashPiece);
            render.appendObject(trashPiece->getSprite());

            trashPiece->setTarget(Point(xSpawn, 200));

        }
    }
};