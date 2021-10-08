#ifndef KJELEDYR_GAME_H
#define KJELEDYR_GAME_H

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "statemachine.h"
#include "asset_manager.h"
#include "input_manager.h"

#include "Game Elements/Playerstruct.h"

// Handles all the managers and combines them

namespace Kjeledyr {

    struct GameData{
        StateMachine stateMachine;
        sf::RenderWindow window;
        AssetManager assetManager;
        InputManager inputManager;

        sf::Music* music;
        bool isSoundOn = true;
        bool isMusicPlaying = false;
        float volumeMusic = 100;

        std::map<int, std::string> highscoresSP;
        std::map<int, std::string> highscoresMP;

        std::vector<std::string> levels;
        int levelChoice;

        std::map<int,struct players*> playerInfo;
        std::vector<int> chosenSprite;
        int numbersOfAI;
    };

    typedef std::shared_ptr<GameData> GameDataRef;

    class Game{
    public:
        Game(unsigned int width, unsigned int height, std::string title);

    protected:
        sf::Clock frameClock;
        const float delta = 1.0f / 60.0f; // FPS
        GameDataRef data = std::make_shared<GameData>(); // Use this pointer to access elements in GameData

        void Run();
    };

}

#endif