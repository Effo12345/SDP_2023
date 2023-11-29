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
#include <functional>



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

void drawInstructions() {

}

void drawStats() {

}

void drawCredits() {

}

void drawMainMenu() {

}

void playGame() {
    bool levelCompleted = false;
    bool returnToMenu = false;

    while(!levelCompleted) {
        std::unique_ptr<GameManager> level1 = std::make_unique<GameManager>(
            "images/backgrounds/1.pic", "level1.wav", levelCompleted, returnToMenu,
             5, 10, 30, 50
        );
        level1->initialize();

        if(returnToMenu)
            return;
    }

    levelCompleted = false;

    while(!levelCompleted) {
        std::unique_ptr<GameManager> level2 = std::make_unique<GameManager>(
            "images/backgrounds/1.pic", "level2.wav", levelCompleted, returnToMenu,
             5, 10, 30, 40
        );
        level2->initialize();

        if(returnToMenu)
            return;
    }

    levelCompleted = false;

    while(!levelCompleted) {
        std::unique_ptr<GameManager> level3 = std::make_unique<GameManager>(
            "images/backgrounds/1.pic", "level3.wav", levelCompleted, returnToMenu,
             5, 10, 30, 20
        );
        level3->initialize();

        if(returnToMenu)
            return;
    }
}


int main() {

//    GameManager level1("images/backgrounds/1.pic", "level1.wav", 30, 10, 30, 50);
//    level1.initialize();

    std::array<std::function<void()>, 4> buttonActions {{
        playGame, drawInstructions, drawStats, drawCredits
    }};


    bool isMainMenu = false;

    std::vector<Button> mainMenu {{
        {{20, 20}, {10, 10}}
    }};
    Button backButton {{0, 0}, {10, 30}};

    Point touchPos;

    while(1) {
        if(!LCD.Touch(&touchPos.x, &touchPos.y))
            continue;

        if(backButton.poll(touchPos)) {
            drawMainMenu();
            backButton.setActive(false);
            continue;
        }

        for(int i = 0; i < mainMenu.size(); i++) {
            if(!mainMenu[i].poll(touchPos))
                continue;

            for(Button& b : mainMenu) {
                b.setActive(false);
            }

            if(i > 0)
                backButton.setActive(true);
            
            buttonActions[i]();
        }
        


        Sleep(50);
    }


    playGame();

   while(1) {
        Sleep(100);
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