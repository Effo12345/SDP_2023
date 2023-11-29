#pragma once

#include <fstream>

class Stats {
    std::string statsFile = "stats/stats.dat";
    
public:
    int trashCollected {};
    int turtlesSaved {};
    int levelsCompleted {};

    void writeStats() {
        std::ofstream write(statsFile);

        write << trashCollected << std::endl
              << turtlesSaved << std::endl
              << levelsCompleted;
        
        write.close();
    }

    void readStats() {
        std::ifstream read(statsFile);

        read >> trashCollected
             >> turtlesSaved
             >> levelsCompleted;
    }
};