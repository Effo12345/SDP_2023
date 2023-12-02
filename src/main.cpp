#include "include/gamemanager.hpp"
#include <functional>
#include <array>

Stats stats;

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

    return 0;
}