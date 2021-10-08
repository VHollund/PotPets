#ifndef KJELEDYR_MENUSTATE_H
#define KJELEDYR_MENUSTATE_H

#include <SFML/Graphics.hpp>
#include <Game Elements/backgroundAnimations.h>

#include "Game Engine/state.h"
#include "Game Engine/game.h"

namespace Kjeledyr {

    class MenuState : public State {
    public:
        MenuState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float delta);
        void Draw(float delta);

    protected:
        GameDataRef data;

        sf::Sprite background;
        sf::Sprite title;
        sf::Sprite playButton;
        sf::Sprite playButtonPressed;
        sf::Sprite highScoreButton;
        sf::Sprite highScoreButtonPressed;
        sf::Sprite exitButton;
        sf::Sprite exitButtonPressed;
        sf::Sprite settingsButton;
        sf::Sprite settingsButtonPressed;
        sf::Sprite soundButton;
        sf::Sprite soundButtonPressed;
        sf::Sprite muteButton;
        sf::Sprite muteButtonPressed;

        backgroundAnimations *backgroundObjects;

        std::map<int, sf::Sprite> pressedButtons;
        std::map<int, sf::Sprite> buttons;
        int hoveredSprite = 0;
        bool up = false;
        bool down = false;
        bool mouseMoved = false;
        bool isPlaySelected = true;
        bool isHighscoreSelected = false;
        bool isExitSelected = false;
        bool isSettingsSelected = false;
        bool isSoundSelected = false;

        std::string mapName = "Map/data/MenuBackground.json";
    };
}


#endif
