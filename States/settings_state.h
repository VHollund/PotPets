#ifndef KJELEDYR_SETTINGS_STATE_H
#define KJELEDYR_SETTINGS_STATE_H

#include <Game Engine/game.h>
#include <Game Engine/state.h>

namespace Kjeledyr {

    class SettingsState : public State {
    public:
        SettingsState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float delta);
        void Draw(float delta);
        long Map(long x, long in_min, long in_max, long out_min, long out_max);

    protected:
        GameDataRef data;

        sf::Sprite background;
        sf::Sprite controllerGuide;
        sf::Sprite musicBar;
        sf::Sprite leftButton;
        sf::Sprite leftHoveredButton;
        sf::Sprite rightButton;
        sf::Sprite rightHoveredButton;
        sf::Sprite soundButton;
        sf::Sprite soundButtonPressed;
        sf::Sprite muteButton;
        sf::Sprite muteButtonPressed;
        sf::Sprite backButton;
        sf::Sprite backButtonPressed;

        sf::RectangleShape musicSlider;
        sf::Text VSyncText;

        std::map<int, sf::Sprite> buttons;
        std::map<int, sf::Sprite> pressedButtons;

        bool mouseMoved = false;
        bool up = false;
        bool down = false;
        bool left = false;
        bool isMusicSelected = true;
        bool isSoundSelected = false;
        bool isRightSelected = false;
        bool isLeftSelected = false;
        bool isMenuSelected = false;

        int hoveredSprite = 0;
        int volumeMin = 5;
        int volumeMax = 680;
        int volumeHeigth = 46;
        int sliderX = 702;
        long musicWidth = sliderX + volumeMax;

        std::string on="ON";
        std::string off="OFF";


    };
}


#endif //KJELEDYR_SETTINGS_STATE_H
