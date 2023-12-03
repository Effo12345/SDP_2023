#pragma once

#include <fstream>

/**
 * @author Ethan Rosati
 * 
 * Holds gameplay statistics data and manages them persistently using file I/O
 **/
class Stats {
    std::string statsFile = "stats/stats.dat";
    
public:
    // Three tracked statistics
    int trashCollected {};
    int turtlesSaved {};
    int levelsCompleted {};

    // File I/O manipulation
    void writeStats();
    void readStats();
};