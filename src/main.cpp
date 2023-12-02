#include "include/main.hpp"
#include "include/point.hpp"
#include "FEHUtility.h"
#include "FEHLCD.h"
#include "include/gameobject.hpp"
#include "include/renderqueue.hpp"
#include "include/boat.hpp"
#include "include/gamemanager.hpp"
#include "include/trash.hpp"
#include "include/button.hpp"
#include "include/stats.hpp"
#include <functional>

Stats stats;

/*
FEHIcon::Icon btns[5];
char labels[][20] = {"Play", "Instructions", "Stats", "Credits"};

FEHIcon::Icon back[1];
char backLabel[1][20] = {"Back"};

std::string backgroundFileNames[] = {"images/backgrounds/credits.pic", "images/backgrounds/instructions.pic", "images/backgrounds/stats.pic"};

void drawBackground (std::string backgroundFileName) {

    FEHImage backgroundImage;

    backgroundImage.Open(backgroundFileName.c_str());

    backgroundImage.Draw(0, 0);

    backgroundImage.Close();

}

void drawBackBtn() {
    FEHIcon::DrawIconArray(back, 1, 1, 0, 210, 0, 270, backLabel, WHITE, WHITE);
}

void menu() {
    FEHIcon::DrawIconArray(btns, 2, 2, 50, 50, 10, 10, labels, WHITE, WHITE);
}

void play() {
    LCD.WriteAt("Play game", 100, 100);
    drawBackBtn();
}

void instructions() {

    drawBackground(backgroundFileNames[1]);

    drawBackBtn();
}

void stats() {

    drawBackground(backgroundFileNames[2]);

    LCD.SetFontColor(WHITE);
    LCD.WriteAt("23", 235, 85);
    LCD.WriteAt("2", 235, 105);
    LCD.WriteAt("3", 235, 125);

    drawBackBtn();
}

void credits() {

    drawBackground(backgroundFileNames[0]);

    drawBackBtn();
}
*/

void drawBackground(std::string path) {
    FEHImage backgroundImage;

    backgroundImage.Open(path.c_str());
    backgroundImage.Draw(0, 0);

    backgroundImage.Close();
}

void drawInstructions() {
    drawBackground("images/menus/instructions.pic");
}

void drawStats() {
    drawBackground("images/menus/stats.pic");

    std::string trashCollected = std::to_string(stats.trashCollected);
    std::string turtlesSaved = std::to_string(stats.turtlesSaved);
    std::string levelsCompleted = std::to_string(stats.levelsCompleted);

    LCD.SetFontColor(WHITE);
    LCD.WriteAt(trashCollected.c_str(), 235, 85);
    LCD.WriteAt(turtlesSaved.c_str(), 235, 105);
    LCD.WriteAt(levelsCompleted.c_str(), 235, 125);
}

void drawCredits() {
    drawBackground("images/menus/credits.pic");
}

void drawMainMenu() {
    drawBackground("images/menus/mainMenu.pic");
}

bool playLevel(std::string bkg, std::string music, std::string gameOver, int trashTarget, int minTrashTime, int maxTrashTime, int dT) {
    bool levelCompleted = false;
    bool returnToMenu = false;

    while(!levelCompleted) {
        std::unique_ptr<GameManager> level = std::make_unique<GameManager>(
            bkg, music, gameOver, levelCompleted, returnToMenu,
             trashTarget, minTrashTime, maxTrashTime, dT
        );
        level->initialize();
        level->updateStats(stats);

        stats.writeStats();

        if(returnToMenu)
            return true;
    }

    return false;
}

void playGame() {
    if(playLevel("images/backgrounds/1.pic", "level1.wav", "images/menus/gameOver_1.pic", 10, 10, 30, 50))
        return;

    if(playLevel("images/backgrounds/2.pic", "level2.wav", "images/menus/gameOver_1.pic", 10, 10, 30, 40))
        return;
    
    if(playLevel("images/backgrounds/3.pic", "level3.wav", "images/menus/gameOver_1.pic", 10, 10, 30, 20))
        return;
}


int main() {

//    GameManager level1("images/backgrounds/1.pic", "level1.wav", 30, 10, 30, 50);
//    level1.initialize();

    
    stats.readStats();

    std::array<std::function<void()>, 4> buttonActions {{
        playGame, drawInstructions, drawStats, drawCredits
    }};


    bool isMainMenu = false;

    std::vector<Button> mainMenu {{
        {{115, 83}, {88, 23}},
        {{60, 115}, {198, 23}},
        {{115, 146}, {88, 23}},
        {{99, 176}, {120, 23}}
    }};
    Button backButton {{3, 3}, {71, 23}};
    backButton.setActive(false);

    Point touchPos;

    SoundManager waves;
    waves.BasePath = "sounds";
    waves.play("waves.wav", 1.0f, true);

    drawMainMenu();

    while(1) {
        if(!LCD.Touch(&touchPos.x, &touchPos.y))
            continue;

        if(backButton.poll(touchPos)) {
            drawMainMenu();
            backButton.setActive(false);

            for(Button& b : mainMenu) {
                b.setActive(true);
            }
            continue;
        }

        for(int i = 0; i < mainMenu.size(); i++) {
            if(!mainMenu[i].poll(touchPos))
                continue;

            if(i > 0) {
                backButton.setActive(true);
                buttonActions[i]();

                for(Button& b : mainMenu) {
                    b.setActive(false);
                }
            }
            else {
                waves.stopSounds();
                buttonActions[0]();

                drawMainMenu();
                waves.play("waves.wav", 1.0f, true);
            }
            break;
        }
        


        Sleep(50);
    }
    

    /*
    std::array<std::function<void()>, 5> screens {{
        menu, play, instructions, stats, credits
    }};

    int btnMode = 0;  // Non-toggle mode
    int renderTarget = 0;
    bool isMainMenu = true;


    while(1) {
        int xTouch, yTouch;

        if(LCD.Touch(&xTouch, &yTouch)) {
            if(!isMainMenu) {
                if(back[0].Pressed(xTouch, yTouch, btnMode)) {
                    renderTarget = 0;
                    isMainMenu = true;
                }
                continue;
            }

            for(int i = 0; i < 5; i++) {
                if(btns[i].Pressed(xTouch, yTouch, btnMode)) {
                    renderTarget = i + 1;
                    isMainMenu = false;
                    break;
                }
            }
        }

        LCD.Clear();
        screens[renderTarget]();

        Sleep(100);
    }
    */

    return 0;
}