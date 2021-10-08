#ifndef KJELEDYR_GAME_OVER_STATE_H
#define KJELEDYR_GAME_OVER_STATE_H

#include "DEFINITIONS.h"
#include "Game Engine/state.h"
#include "Game Engine/game.h"

namespace Kjeledyr{

    class GameOverState : public State {

    public:
        GameOverState(GameDataRef data, int score, int winner, bool singleplayer);
        void Init();
        void HandleInput();
        void Update(float delta);
        void Draw(float delta);
        bool CheckForHighscore(std::map<int, std::string> highscore, int score);
        void SaveHighscore(std::map<int, std::string> highscores);
        void LoadHighscores();
        void LoadAlphabet();
        sf::Sprite SetHeadTexture(int spriteOffSet);
        void LoadHead();

    protected:
        GameDataRef data;

        sf::FloatRect textRect;
        sf::Font font;
        sf::Text scoreString;
        sf::Text max10Chars;
        sf::Text name;
        std::string nameEntered;
        sf::Text previewCh;
        std::map<int, char> alphabet;
        char currentCh;
        int currentKey = 0;
        int alphaEnd;

        int ControllerID;
        bool isAI;

        int score;
        int winner;

        bool singlePlayer; // true = singlePlayer, false = multiplayer
        bool newHighscore;
        bool charSelect = false;

        sf::Sprite gameOverBackground;
        sf::Sprite newHighscoreBackground;
        sf::Sprite okButton;
        sf::Sprite okButtonPressed;
        sf::Sprite menuButton;
        sf::Sprite menuButtonPressed;
        sf::Sprite highScoreButton;
        sf::Sprite highScoreButtonPressed;

        sf::Sprite head;

        std::map<int, sf::Sprite> menuOptions;
        int hoveredSprite = 0;
        bool mouseMoved = false;
        bool right = false;
        bool left = false;
        bool isMenuSelected = true;
        bool isHighscoreSelected = false;
        bool isOKSelected = false;
    };

}


#endif