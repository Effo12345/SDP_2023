#include "include/trash.hpp"

    Trash::Trash(Point spawnLocation, int trashIndex)
    : GameObject(spawnLocation, 1.0f) {  // TODO: Why no take maxSpeed instead of magic number?
        setTarget(Point(spawnLocation.x, targetY));

        for(int i = 0; i < trashFolders[trashIndex].second; i++) {
            introAnim.push_back(
                std::make_shared<Sprite>(trashFolders[trashIndex].first + std::to_string(i + 1) + ".pic")
            );
        }

        gamePos = gamePos + spawnOffsets[trashIndex];

        sprite = std::make_shared<Sprite>(trashFolders[trashIndex].first + "full.pic");
    }

    void Trash::draw() {
        if(introIter < introAnim.size()) {
            introAnim[introIter]->setPos(gamePos - (spriteSize / 2));
            introAnim[introIter]->draw();

            introIter++;

            return;
        }

        sprite->setPos(gamePos - spriteSize / 2);
        sprite->draw();
    }