#pragma once

#include <fstream>

class Stats {
    std::string statsFile = "stats/stats.dat";
    
public:
    int trashCollected {};
    int turtlesSaved {};
    int levelsCompleted {};

    void writeStats();

    void readStats();
};