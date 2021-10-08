#ifndef KJELEDYR_PLAYER_H
#define KJELEDYR_PLAYER_H

#include <SFML/Graphics.hpp>
#include "PlayerObject.h"

namespace Kjeledyr {

    class Player : public PlayerObject {
    public:
        Player(int ChosenSprite, std::vector<std::pair<int, int>> &spawnPoints);
        int GetControllerID();
        void SetControllerID(int ID);
        void SetSpriteID(int ID);
        void HandleInput(std::map<int,PlayerObject*> allPlayers, GameDataRef &data);

    protected:
        unsigned int controllerID;
    };
}
#endif
