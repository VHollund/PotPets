#ifndef KJELEDYR_HIGHSCORE_STATE_H
#define KJELEDYR_HIGHSCORE_STATE_H

#include "Game Engine/state.h"
#include "Game Engine/game.h"

namespace Kjeledyr {

    class HighscoreState : public State {
    public:
        HighscoreState(GameDataRef data);
        void Init();
        void HandleInput();
        void Update(float delta);
        void Draw(float delta);
        void LoadHighscores();
        void LoadHighscoreInfo(std::map<int, std::string> SPmap, std::map<int, std::string> MPmap);

    protected:
        GameDataRef data;

        sf::Font font;

        sf::Text rank;
        std::vector<sf::Text> SPranks;
        std::vector<sf::Text> MPranks;

        sf::Text name;
        std::vector<sf::Text> SPnames;
        std::vector<sf::Text> MPnames;

        sf::Text score;
        std::vector<sf::Text> SPscores;
        std::vector<sf::Text> MPscores;

        std::map<int, sf::Sprite> menuOptions;
        sf::Sprite background;
        sf::Sprite backButton;
        sf::Sprite backPressedButton;
        sf::Sprite spButton;
        sf::Sprite spPressedButton;
        sf::Sprite mpButton;
        sf::Sprite mpPressedButton;

        int hoveredSprite = 1;
        bool left = false;
        bool right = false;
        bool mouseMoved = false;
        bool isBackPressed = false;
        bool isSingleplayerPressed = true;
        bool isMultiplayerPressed = false;
    };
};


#endif //KJELEDYR_HIGHSCORE_STATE_H
