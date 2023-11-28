#include "include/main.hpp"
#include "include/point.hpp"
#include "FEHUtility.h"
#include "FEHLCD.h"
#include "include/gameobject.hpp"
#include "include/renderqueue.hpp"
#include "include/boat.hpp"
#include "include/gamemanager.hpp"
#include "include/trash.hpp"
#include <functional>

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


int main() {

   GameManager level1("images/backgrounds/1.pic", 10, 30, 50);
   level1.initialize();

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
            if(!isMainMenu && back[0].Pressed(xTouch, yTouch, btnMode)) {
                renderTarget = 0;
                isMainMenu = true;
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