#include "include/gamemanager.hpp"

/**
 * @author Ethan Rosati
 * 
 * Construct a new GameManager object with correct assets and tunable parameters
 * 
 * @param bkgFile Filepath to background image (.pic)
 * @param musicFile Filename for music (.wav)
 * @param gameOverFile Filepath to level failed menu (.pic)
 * @param success Reference bound to member variable. Tracks if player completed level
 * @param quit Reference bound to member variable. Tracks if player requested main menu
 * @param targetTrash Amount of trash to collect to beat the level
 * @param minTrashTime Minimum number of cycles between each trash spawn
 * @param maxTrashTime Maximum number of cycles between each trash spawn
 * @param timeStep Length of time between each frame (ms)
 */
GameManager::GameManager(std::string bkgFile, std::string musicFile, std::string gameOverFile, // ^
    bool &success, bool &quit,                                                                 // | Params
    int targetTrash, int minTrashTime, int maxTrashTime, int timeStep)                         // v
: musicPath{musicFile}, completedLevel{success}, exitToMenu{quit},                             // ^
  trashCollectionTarget{targetTrash}, minSpawnCycles{minTrashTime},                            // | Initializer list
  maxSpawnCycles{maxTrashTime}, dT{timeStep} {                                                 // v
    bkg = std::make_shared<Sprite>(bkgFile);                                                   // Executable statements
    // Pass boat all the sprites it needs                                                      // |
    // make_shared(sprite array, starting pos, sprite dimensions, max speed)                   // v
    boat = std::make_shared<Boat>(std::vector<std::string>{
        "images/boat/up.pic",
        "images/boat/right.pic",
        "images/boat/down.pic",
        "images/boat/left.pic"
    }, initialBoatPos, Point(32, 35), 4);

    // Buoy is inactive until the player gives touch input
    target = std::make_shared<Sprite>("images/target.pic");
    target->setActive(false);

    // Draw fail screen in top left corner
    failScreen = std::make_shared<Sprite>(gameOverFile, Point{0, 0});

    fillTurtleArray();
}

/**
 * @author Ethan Rosati
 * 
 * Spawns trash at the top of the screen based on input position. Ensures trash
 * is rendered and can be interacted with correctly
 * 
 * @param xSpawn The x-coordinate of the trash's spawn location
 * @param trashIndex 0-2 index of which trash to spawn
 **/
void GameManager::spawnTrash(int xSpawn, int trashIndex) {
    // Create new trash then add it to trash array and render queue.
    std::shared_ptr<Trash> tmp = std::make_shared<Trash>(Point(xSpawn, 0), trashIndex);
    trash.push_back(tmp);
    render.appendObject(tmp);
}

/**
 * @author Ethan Rosati
 * 
 * Checks whether all currently active pieces of trash are colliding with the
 * boat for the current update
 **/
void GameManager::checkTrashCollision() {
    // Loop throught all pieces of trash
    for(int i = 0; i < trash.size();) {
        // If the boat is colliding with the trash
        if(boat->isColliding(trash[i]->getPos())) {
            // Remove the trash from the render queue and trash array
            trash[i]->destroy();
            trash.erase(trash.begin() + i);

            // Player collected a piece of trash
            trashCollected++;

            soundManager.play("pickupTrash.wav", 0.25f);
            continue;
        }

        // Only increment index if the current piece of trash wasn't destroyed.
        // trash.erase() shifts all members after the current value forward
        // by one index
        i++;
    }
}

/**
 * @author Ethan Rosati
 * 
 * Hard clamp the touch input to be between a prescribed set of values. Ensures
 * the boat can't leave the edges of the screen or go onto the beach.
 * 
 * @param touchPos Input point position. Modified by reference
 **/
void GameManager::boundsCheckTouch(Point& touchPos) {
    // VSCode throws an error here since it doesn't realize the compiler
    // supports c++17. Still compiles correctly
    //           std::clamp(value, low, high);
    touchPos.x = std::clamp(touchPos.x, minTouch.x, maxTouch.x);
    touchPos.y = std::clamp(touchPos.y, minTouch.y, maxTouch.y);
}

/**
 * @author Ethan Rosati
 * 
 * Completely destroy the turtle object with the highest index.
 **/
void GameManager::killTurtle() {
    // Remove turtle from render queue an from array
    turtles[turtles.size() - 1]->destroy();
    turtles.pop_back();

    soundManager.play("turtleDeath.wav", 1.0f);
}

/**
 * @author Ethan Rosati
 * 
 * Play the animation of turtles swimming out to sea and screen wipe once the 
 * player completes a level. Sets boolean references so main function knows to 
 * proceed to the next level.
 **/
void GameManager::levelCompleted() {
    // Stop current music and replace with success jingle
    soundManager.stopSounds();
    Sleep(500);
    soundManager.play("savedTurtles.wav");

    // Remove all on-screen objects but turtles and background
    for(auto& t : trash)
        t->destroy();
    trash.clear();
    boat->destroy();
    target->destroy();

    // Set the turtles' target for swimming out to sea. Swims straight forward
    for(auto& t : turtles)
        t->setTarget(Point(t->getPos().x, turtleTargetY));

    // Have a consistent timestep between both parts of the end level animation
    int exitAnimDt = 2;

    // Loop through turtle movement for a certain length of time
    float animTime = 1.0f;  // seconds
    float startTime = TimeNow();
    while(TimeNow() - startTime < animTime) {
        // Move all turtles
        for(auto& t : turtles)
            t->moveTowards();

        render.draw();
        Sleep(exitAnimDt);
    }

    // The screen wipe animation uses Proteus rectangles that must go on top of
    // existing objects, so the render queue can no longer be responsible for
    // calling LCD.Update(). Not doing this causes extreme flickering.
    render.doUpdateLcd(false);

    // Animation to gradually cover the screen with a black rectangle
    for(int i = 0; i < 241; i += 12) {
        for(auto& t : turtles)
            t->moveTowards();

        // Draw normal on-screen objects... 
        render.draw();

        // ... then override them with a black rectangle that stretches the
        // width of the screen
        LCD.SetFontColor(BLACK);
        LCD.FillRectangle(0, 0, 320, i);

        // Now call update after ALL on-screen elements have been drawn
        LCD.Update();

        Sleep(exitAnimDt);
    }

    // Sleep to let the victory jingle finish
    Sleep(1250);

    // Let main function know level was completed successfully
    completedLevel = true;
    exitToMenu = false;
}


/**
 * @author Ethan Rosati
 * 
 * Displays the level failed screen and instantiates the buttons necessary to 
 * make it interactable
 **/
void GameManager::levelFailed() {
    // Stop music and replace it with failure sound
    soundManager.stopSounds();
    Sleep(500);
    soundManager.play("killedTurtles.wav");

    // Add game over screen to the top of the draw order, then draw new fram
    render.appendObject(failScreen);
    render.draw();

    // Create buttons that track whether player wants to retry level or return
    // to main menu. Point are the buttons' positions and sizes
    Button replay {Point{116, 94}, Point{87, 23}};
    Button exit {Point{83, 133}, Point{152, 23}};
    Point touchPos;

    // Continue polling buttons until the player clicks on one of them
    bool validInput = false;
    while(!validInput) {
        // No point checking anything else if there was no touch input this update
        if(!LCD.Touch(&touchPos.x, &touchPos.y))
            continue;

        if(replay.poll(touchPos)) {
            // Tell main function to repeate the current level
            exitToMenu = false;
            validInput = true;
        }
        else if(exit.poll(touchPos)) {
            // Tell main function to return to main menu
            exitToMenu = true;
            validInput = true;
        }

        Sleep(dT);
    }

    // Level was not completed. Don't increment the stat counter
    completedLevel = false;
}

/**
 * @author Ethan Rosati
 * 
 * Fill the member variable turtle array with three turtles. These turtles
 * are evenly spaced with coordinates set by member variables. A random speed is
 * generated for each one to make the victory animation look more natural
 **/
void GameManager::fillTurtleArray() {
    // Instantiate randomizer
    std::random_device r;
    std::default_random_engine eng(r());
    std::uniform_int_distribution<int> turtleSpeed(minTurtleSpeed, maxTurtleSpeed);

    // Fill the array based on the player's number of lives
    for(int i = 0; i < numLives; i++) {
        //make_shared(starting position, sprite size, speed)
        turtles.push_back(std::make_shared<Turtle>
            (Point(turtleXPose + turtleSpacing * i, turtleYPose), Point(16, 16), turtleSpeed(eng))
        );
    }
}

/**
 * @author Ethan Rosati
 * 
 * Begins a while loop that runs each level. Manages the movement and interaction
 * of all on-screen objects (player, trash, turtles). Spawns new trash based on
 * randomized values. Polls touch input and sends to composed classes
 * This function only returns once the level ends.
 **/
void GameManager::update() {
    // Track the randomized number of cycles until the next trash spawn
    int cyclesUntilSpawn {};

    // Instantiate randomizers to randomize trash spawn time, location, and type
    std::random_device r;
    std::default_random_engine eng(r());
    std::uniform_int_distribution<int> spawnTime(minSpawnCycles, maxSpawnCycles);
    std::uniform_int_distribution<int> spawnLocation(minSpawnX, maxSpawnX);
    std::uniform_int_distribution<int> trashIndex(minTrashIndex, maxTrashIndex);

    // Set the touch pos as the boat's starting position to ensure the player is
    // stationary at the start of the level
    Point touchPos = initialBoatPos;

    while(true) {
        // Spawn a new piece of trash if the cycle counter has dropped to zero
        if(!cyclesUntilSpawn) {
            spawnTrash(spawnLocation(eng), trashIndex(eng));
            // Generate number of cycles until the next spawn
            cyclesUntilSpawn = spawnTime(eng);
        }

        // Spawn counter decrements by one every cycle
        cyclesUntilSpawn--;

        // Updates the position of all trash
        for(int i = 0; i < trash.size();) {
            if(!trash[i]->hasReachedTarget()) {
                // Keep moving towards the beach if the trash hasn't reached its
                // target
                trash[i]->moveTowards();

                // Only increment if trash WASN'T removed from the array
                i++;
            }
            else {
                // If trash reached the beach, remove it from the array,
                // kill a turtle, and decrement the player's remaining lives
                trash.erase(trash.begin() + i);
                killTurtle();
                numLives--;
            }
        }

        // If the player's lives drop to 0, they failed.
        if(numLives < 1) {
            levelFailed();
            // Quit level loop
            break;
        }

        // If the player collected enough trash, they succeeded
        if(trashCollected >= trashCollectionTarget) {
            levelCompleted();
            // Quit level loop
            break;
        }
        
        // If the screen was touched since last update,
        if(LCD.Touch(&touchPos.x, &touchPos.y)) {
            // Clamp touch between acceptable values, then set boat's target and
            // update buoy's position
            boundsCheckTouch(touchPos);
            boat->setTarget(touchPos);
            target->setPos(touchPos - (targetSize / 2));
        }

        // Move the boat towards its target so long as it hasn't reached it
        if(!boat->hasReachedTarget()) {
            boat->moveTowards();
            // Buoy should be visible until the boat reaches its goal
            target->setActive(true);
        }

        // Check if the boat has collided with any trash
        checkTrashCollision();

        // Call draw AFTER all other updates have been made, then sleep
        render.draw();
        Sleep(dT);
    }
}

/**
 * @author Ethan Rosati
 * 
 * Initialize member variables then call update to begin the level
 **/
void GameManager::initialize() {
    // Put all previosuly instantiated objects on the render queue in preparation
    // for being drawn
    render.appendObject(bkg);
    render.appendObject(target);
    render.appendObject(boat);

    for(auto& turtle : turtles)
        render.appendObject(turtle);

    // Sleep then clear touch buffer to reject touch inputs bleeding over from
    // the main menu
    Sleep(100);
    LCD.ClearBuffer();

    // Set soundManager's target folder then start playing level music
    soundManager.BasePath = "sounds";
    soundManager.play(musicPath.c_str(), 0.75f, true);

    // Start level
    update();
}

/**
 * @author Ethan Rosati
 * 
 * Update the values stored in a stats struct based on member variables tracking
 * what happened in the level. Should only be called after the level is completed
 * 
 * @param stats Stats struct to be modified by reference
 **/
void GameManager::updateStats(Stats& stats) {
    stats.trashCollected += trashCollected;
    stats.turtlesSaved += numLives;

    if(completedLevel) {
        stats.levelsCompleted++;
    }
}