#pragma once

#include "gameobject.hpp"
#include "renderqueue.hpp"
#include "FEHUtility.h"
#include "boat.hpp"
#include "trash.hpp"
#include <random>
#include <algorithm>
#include "soundmanager.hpp"
#include "stats.hpp"
#include "turtle.hpp"
#include "button.hpp"

/**
 * @author Ethan Rosati
 * 
 * Manages all aspects of gameplay within each individual level. The update 
 * function runs the level itself while other ancillary functions are either 
 * called by update or help initialize member variables.
 **/
class GameManager {
    Point initialBoatPos = {160, 130};

    // All objects to be rendered
    std::shared_ptr<Sprite> bkg;
    std::shared_ptr<Boat> boat;
    std::shared_ptr<Sprite> target;
    std::vector<std::shared_ptr<Turtle>> turtles;
    std::vector<std::shared_ptr<Trash>> trash;
    std::shared_ptr<Sprite> failScreen;

    // Renderer
    RenderQueue render;

    SoundManager soundManager;
    std::string musicPath;
    
    // References bound in constructor. Modify variables in the main function
    bool &completedLevel;
    bool &exitToMenu;

    int numLives = 3;
    int turtleXPose = 135;
    int turtleYPose = 185;
    int turtleSpacing = 20;
    int turtleTargetY = 10;

    // Size of buoy sprite
    Point targetSize {16, 16};

    // Extrema of allowable touch positions
    Point minTouch{20, 20};
    Point maxTouch{299, 150};

    //
    // Parameters for trash spawning
    //
    int minSpawnCycles = 10;
    int maxSpawnCycles = 30;

    int minSpawnX = 10;
    int maxSpawnX = 300;

    int minTrashIndex = 0;
    int maxTrashIndex = 3;

    int trashCollectionTarget {};
    int trashCollected {};

    // Extrema for turtle swim speed
    int minTurtleSpeed = 1;
    int maxTurtleSpeed = 3;

    // Length of time between updates (ms)
    int dT = 50;

    void spawnTrash(int xSpawn, int trashIndex);
    void checkTrashCollision();

    void boundsCheckTouch(Point& touchPos);

    void killTurtle();

    void levelCompleted();
    void levelFailed();

    void fillTurtleArray();

    void update();

public:
    GameManager(std::string bkgFile, std::string musicFile, std::string gameOverFile,
        bool &success, bool &quit, 
        int targetTrash, int minTrashTime, int maxTrashTime, int timeStep = 50);

    void initialize();

    void updateStats(Stats& stats);
};