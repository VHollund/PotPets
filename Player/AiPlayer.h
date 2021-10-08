#ifndef KJELEDYR_AIPLAYER_H
#define KJELEDYR_AIPLAYER_H

#include <Game Elements/AiRoutes.h>
#include "PlayerObject.h"

namespace Kjeledyr {

    class AiPlayer : public PlayerObject {
    public:
        AiPlayer(int ChosenSprite, std::vector<std::pair<int, int>> &spawnPoints);
        void findTarget(std::map<int, PlayerObject*> players); //std::vector<PlayerObject> players
        void moveDir(std::vector<AiRoutes*> routes,std::map<int,PlayerObject*> Allplayers);
        void UpRight();
        void UpLeft();
        void FindRoute(std::vector<AiRoutes*> routes);
        void UseRoute(AiRoutes* route);
        bool CheckIfTrapped();
        void SetTrapped(bool trapped);
    protected:
        int focus;//direction Ai has to focus while choosing route. check definitions for direction specifics
        int Xdirection;
        int Ydirection;
        int oldY=0;
        PlayerObject* last;
        PlayerObject* currentTar;
        sf::RectangleShape rect;
        bool trapped = false;
    };
}


#endif //KJELEDYR_AIPLAYER_H
