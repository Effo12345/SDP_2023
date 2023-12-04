#include "include/gamemanager.hpp"
#include <functional>
#include <array>

// Create stats object to hold values displayed in main menu and to be passed to
// GameManager objects
Stats stats;

/**
 * @author Owen Chevalier
 * 
 * Draw a background image (one that covers the entire screen)
 * 
 * @param path Filepath to the .pic file to draw
**/
void drawBackground(std::string path) {
    FEHImage backgroundImage;

    // Open image from filepath, draw it, then close the file
    backgroundImage.Open(path.c_str());
    backgroundImage.Draw(0, 0);

    backgroundImage.Close();
}

/**
 * @author Ethan Rosati
 * 
 * Draw the instructions sprite 
**/
void drawInstructions() {
    drawBackground("images/menus/instructions.pic");
}

/**
 * @author Ethan Rosati
 * 
 * Draw the statistics sprite, then write the statistics overtop of it using 
 * LCD.WriteAt 
**/
void drawStats() {
    drawBackground("images/menus/stats.pic");

    // Create strings from the values in the stats struct
    std::string trashCollected = std::to_string(stats.trashCollected);
    std::string turtlesSaved = std::to_string(stats.turtlesSaved);
    std::string levelsCompleted = std::to_string(stats.levelsCompleted);

    // Write those strings to the screen at the correct coordinates
    LCD.SetFontColor(WHITE);
    LCD.WriteAt(trashCollected.c_str(), 235, 85);
    LCD.WriteAt(turtlesSaved.c_str(), 235, 105);
    LCD.WriteAt(levelsCompleted.c_str(), 235, 125);
}

/**
 * @author Ethan Rosati
 * 
 * Draw the credits sprite
**/
void drawCredits() {
    drawBackground("images/menus/credits.pic");
}

/**
 * @author Ethan Rosati
 * 
 * Draw the main menu
**/
void drawMainMenu() {
    drawBackground("images/menus/mainMenu.pic");
}

/**
 * @author Ethan Rosati
 * 
 * Play the level specified by the parameters while managing level replay and
 * exit to menu
 * 
 * @param bkg Filepath to .pic background file to be drawn as the base layer
 * @param music File name of music (.wav)
 * @param gameOver Filepath to .pic of game over screen
 * @param trashTarget Amount of trash required to beat the level
 * @param minTrashTime Minimum number of frames between each trash spawn
 * @param maxTrashTime Maximum number of frames between each trash spawn
 * @param dT Amount of time between each frame (ms)
**/
bool playLevel(std::string bkg, std::string music, std::string gameOver, 
               int trashTarget, int minTrashTime, int maxTrashTime, int dT) {
    // Create boolean flags to be modifed by reference in the GameManager
    bool levelCompleted = false;
    bool returnToMenu = false;

    // Continue looping until ther user completes the level or quits to menu
    while(!levelCompleted) {
        // Instantiate new GameManager object
        std::unique_ptr<GameManager> level = std::make_unique<GameManager>(
            bkg, music, gameOver, levelCompleted, returnToMenu,
            trashTarget, minTrashTime, maxTrashTime, dT
        );
        // Initialize starts the level
        level->initialize();

        // Control returns here once the level is completed
        // Update stats from the level and save to file
        level->updateStats(stats);
        stats.writeStats();

        // If the player requested to return to the main menu, let the caller
        // know
        if(returnToMenu)
            return true;

        // Auto-scaling difficulty. If a player loses, decrease the amount of 
        // trash they need to collect to beat the level and reduce the trash
        // spawn rate
        trashTarget -= 3;
        minTrashTime += 2;
        maxTrashTime += 2;
        
        // If the player beat the level, GameManager sets levelCompleted to true
        // by reference, so the loop exits
    }

    // If the player exited the level normally, return false
    return false;
}

/**
 * @author Ethan Rosati
 * 
 * Play through each of the 3 levels, passing the correct assets and parameters
 * for each one. Checks if the player requested to return to the main menu after
 * every level
**/
void playGame() {
    // If the player wants to return to the main menu, exit the function early
    // and return control to the caller
    if(playLevel("images/backgrounds/1.pic", "level1.wav", "images/menus/gameOver_1.pic", 15, 25, 40, 50))
        return;

    if(playLevel("images/backgrounds/2.pic", "level2.wav", "images/menus/gameOver_2.pic", 25, 10, 30, 40))
        return;
    
    if(playLevel("images/backgrounds/3.pic", "level3.wav", "images/menus/gameOver_3.pic", 40, 10, 20, 20))
        return;
}

/**
 * @author Ethan Rosati
 * 
 * Called upon game startup. Manages rendering the main menu and processing
 * player input.
 **/
int main() {
    // Read in stats data on game startup
    stats.readStats();

    // Assign function callbacks for each button based on index
    std::array<std::function<void()>, 4> buttonActions {{
        playGame, drawInstructions, drawStats, drawCredits
    }};

    // Define the positions and sizes of all 4 buttons that make up the main menu
    std::vector<Button> mainMenu {{
        {{115, 83}, {88, 23}},
        {{60, 115}, {198, 23}},
        {{115, 146}, {88, 23}},
        {{99, 176}, {120, 23}}
    }};
    // Back button placed on submenus. Inactive by default since the game starts
    // on the main menu
    Button backButton {{3, 3}, {71, 23}};
    backButton.setActive(false);

    // Hold the most recent position the player touch on screen
    Point touchPos;

    // Create wave crashing sound effect that loops while the player is on the 
    // main menu
    SoundManager waves;
    waves.BasePath = "sounds";
    waves.play("waves.wav", 1.0f, true);

    // Draw main menu before loop so something appears on startup
    drawMainMenu();

    // This loop actually runs infinitely. Nothing can break out of it or return
    // early but closing the program
    while(1) {
        // Since this loop manages the menu, if there were no touches input,
        // there's no point checking anything else
        if(!LCD.Touch(&touchPos.x, &touchPos.y))
            continue;

        // Check if the back button is pressed
        // If the back button is inactive, this will immediately return false
        if(backButton.poll(touchPos)) {
            // Back button returns to the main menu. Make back button inactive...
            drawMainMenu();
            backButton.setActive(false);

            // ... and all the main menu buttons active again
            for(Button& b : mainMenu) {
                b.setActive(true);
            }
            continue;
        }

        // Check all main menu buttons
        for(int i = 0; i < mainMenu.size(); i++) {
            // If the button wasn't pressed, no use looking any further
            if(!mainMenu[i].poll(touchPos))
                continue;

            // If the button isn't the play button, activate the associated sub-menu
            if(i > 0) {
                // Activate back button, draw sub-menu, and deactivate main menu
                backButton.setActive(true);
                buttonActions[i]();

                for(Button& b : mainMenu) {
                    b.setActive(false);
                }
            }
            else {
                // If the button pressed was the play button, stop menu noises
                // then start playing the game
                waves.stopSounds();
                buttonActions[0]();

                // Control returns here either when the player beats the game or 
                // returns to the menu

                // Redraw the main menu onto the screen, then start playing 
                // menu sound again
                drawMainMenu();
                waves.play("waves.wav", 1.0f, true);
            }

            // The correct button input was found, so stop looking. Also 
            // implements a moderate level of spam protection
            break;
        }
        
        // No need to check super often, as long as the menu stays responsive
        Sleep(50);
    }

    return 0;
}