#ifndef KJELEDYR_GAME_STATE_H
#define KJELEDYR_GAME_STATE_H


#include "Game Engine/state.h"
#include "Game Engine/game.h"
#include <Game Elements/backgroundAnimations.h>
#include <Game Elements/powerUp.h>
#include <string>

#include "Map/object.h"

#include <Player/AiPlayer.h>
#include "Player/player.h"
#include <list>
#include <Map/map.h>


namespace Kjeledyr {

    class Object;

    class GameState : public State {

    public:
        GameState(GameDataRef data, bool singleplayer);
        void Init();
        void HandleInput();
        void Update(float delta);
        void Draw(float delta);

        void Gametime();
        void GotoGameOver();
        void GameScore();
        void Heads();
        int GetRandomNumber(int min, int max); //Get a random number within a range
        void SpawnPowerUp();
        void Music();
        sf::Sprite SetHeadTexture(int spriteOffSet);

    protected:
        GameDataRef data;

        int score;
        bool singleplayer;

        AiPlayer* AIPlayer;
        Player* player;

        std::vector<sf::Text> scoreTexts;
        std::vector<sf::Sprite> charHeads;

        std::map<int,PlayerObject*> Allplayers;
        std::map<int,AiPlayer*> AIplayers;
        std::map<int,Player*> Players;

        std::vector<AiRoutes*> routes;
        std::vector<sf::RectangleShape> locat;

        backgroundAnimations *backgroundObjects;
        bool drawBackgroundObjects;

        powerUp *powerUps[3];
        powerUp *currentPower = nullptr;

        sf::Font font;
        sf::Text timerText;
        std::string timers;
        int timer1 = 0;
        int timer2 = 4;
        int timer3 = 0;
        int timer4 = 0;

        sf::Clock clock;
        int powerTimer;
        const int pMinTime = 5; //powerup minimum spawntime
        const int pMaxTime = 10; //powerup maximum spawntime

        sf::Clock gameClock;

        sf::Sprite _background;

        std::list<Object*> objects;
        std::list<Object*> collisionLayer;
        std::vector<std::pair<int, int>> powerUpSpawns;
        std::vector<std::pair<int, int>> spawnPoints;

        std::vector<std::pair<std::pair<int, int>, int>> triggerPoints;

        std::map<std::pair<int, int>, Tile*> collisionTiles; // <<col, row>, tile>

        std::string mapName; //Change this string to choose which map to Load
    };
}

#endif
