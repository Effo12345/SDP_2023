#include "include/stats.hpp"

void Stats::writeStats() {
    std::ofstream write(statsFile);

    if(!write.good())
        return;

    write << trashCollected << std::endl
            << turtlesSaved << std::endl
            << levelsCompleted;
    
    write.close();
}

void Stats::readStats() {
    std::ifstream read(statsFile);

    read >> trashCollected
            >> turtlesSaved
            >> levelsCompleted;
}