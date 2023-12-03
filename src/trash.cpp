#include "include/trash.hpp"

/**
 * @author Ethan Rosati
 * 
 * Construct a new Trash object and build a base class GameObject using an
 * initializer list
 * 
 * @param spawnLocation Starting position for the trash
 * @param trashIndex Type of trash to spawn (only changes appearance)
 **/
Trash::Trash(Point spawnLocation, int trashIndex)
: GameObject(spawnLocation, maxSpeed) {
    // Trash moves vertically towards the beach
    setTarget(Point(spawnLocation.x, targetY));

    // Fill the intro animation array with sprites that grow the trash by 1
    // vertical pixel each update
    for(int i = 0; i < trashFolders[trashIndex].second; i++) {
        introAnim.push_back(
            std::make_shared<Sprite>(trashFolders[trashIndex].first + std::to_string(i + 1) + ".pic")
        );
    }

    // Offset the spawn position based on trash type
    gamePos = gamePos + spawnOffsets[trashIndex];

    // Initialize sprite of full trash
    sprite = std::make_shared<Sprite>(trashFolders[trashIndex].first + "full.pic");
}

/**
 * @author Ethan Rosati
 * 
 * Draw the trash to the screen. Use the introAnim sprites while the trash is
 * first entering the screen, then the full sprite after.
 **/
void Trash::draw() {
    // Draw the intro animation trash sprite while there are stil sprites left
    if(introIter < introAnim.size()) {
        // Update render position then draw
        introAnim[introIter]->setPos(gamePos - (spriteSize / 2));
        introAnim[introIter]->draw();

        // Track the number of frames the trash has been transitioning in for
        introIter++;

        return;
    }

    // If the intro animation is complete, draw the full sprite
    sprite->setPos(gamePos - spriteSize / 2);
    sprite->draw();
}