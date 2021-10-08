#ifndef KJELEDYR_LEVELSELECT_STATE_H
#define KJELEDYR_LEVELSELECT_STATE_H


#include <Game Engine/game.h>

namespace Kjeledyr {
    class LevelSelectState : public State {
    public:
        LevelSelectState(GameDataRef data, bool singleplayer);
        void Init();
        void HandleInput();
        void Update(float delta);
        void Draw(float delta);

    protected:
        GameDataRef data;
        bool singleplayer;

        int currentSprite = 1;
        sf::Sprite levelBackground;
        sf::Sprite level1;
        sf::Sprite level2;
        sf::Sprite level3;
        sf::Sprite leftButton;
        sf::Sprite rightButton;
        sf::Sprite hoveredLeftButton;
        sf::Sprite hoveredRightButton;

        std::map<int, sf::Sprite> buttons;
        std::map<int, sf::Sprite> pressedButtons;
        std::vector<sf::Sprite> levels;

        sf::Font font;
        sf::Text levelName;
        sf::FloatRect textRect;

        sf::Clock clockJoystick;
        int minTimeJoystick = 300;
        int lastTimePressed = 200;

        bool isLevelOneSelected;
        bool isLevelTwoSelected;
        bool isLevelThreeSelected;
        bool isHoveredLeft;
        bool isHoveredRight;
        bool isMouseMoved;

        long long int levelChoice = 0;
        long long int buttonChoice = 0;

        void GoToGameState();
    };

}
#endif //KJELEDYR_LEVELSELECT_STATE_H
