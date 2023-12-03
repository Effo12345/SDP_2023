#include "include/stats.hpp"

/**
 * @author Ethan Rosati
 * 
 * Write stats in memory to a file specified by a member variable
 **/
void Stats::writeStats() {
    // Open file using ofstream constructor
    std::ofstream write(statsFile);

    // Only write if the file opens correctly
    if(!write.good())
        return;

    // Write all data in class to file
    write << trashCollected << std::endl
            << turtlesSaved << std::endl
            << levelsCompleted;
    
    // Not strictly necessary, but called explicitly
    write.close();
}

/**
 * @author Ethan Rosati
 * 
 * Read stats from a file specified by a member variable and use it to fill
 * the data in this class instance
 **/
void Stats::readStats() {
    // Open file using ifstream constructor
    std::ifstream read(statsFile);

    // Only read if the file opens correctly since persistent stats are 
    // non-essential
    if(!read.good())
        return;

    // Input all three tracked statistics
    read >> trashCollected
            >> turtlesSaved
            >> levelsCompleted;
}