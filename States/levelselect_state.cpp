#include <DEFINITIONS.h>
#include "levelselect_state.h"
#include "game_state.h"

namespace Kjeledyr{

    LevelSelectState::LevelSelectState(GameDataRef data, bool singleplayer) : data(data), singleplayer(singleplayer){}

    void LevelSelectState::Init() {
        levelBackground.setTexture(this->data->assetManager.GetTexture("Level State Background")); // Level Background

        font = data->assetManager.GetFont("Berlin Sans FB"); //Sets the text
        levelName.setFont(font);
        levelName.setCharacterSize(80);
        levelName.setPosition(800, 900);

        //Sets the images for the levels in an array
        level1.setTexture(this->data->assetManager.GetTexture("Level 1"));
        level1.setScale(0.95,0.95);
        level1.setPosition(275, 90);

        level2.setTexture(this->data->assetManager.GetTexture("Level 2"));
        level2.setScale(0.95,0.95);
        level2.setPosition(275, 90);

        level3.setTexture(this->data->assetManager.GetTexture("Level 3"));
        level3.setScale(0.95,0.95);
        level3.setPosition(275, 90);

        levels.push_back(level1);
        levels.push_back(level2);
        levels.push_back(level3);

        //Sets left and right button
        leftButton.setTexture(this->data->assetManager.GetTexture("Left button"));
        leftButton.setScale(0.35,0.35);
        leftButton.setPosition(500, 900);

        hoveredLeftButton.setTexture(this->data->assetManager.GetTexture("Left Hovered"));
        hoveredLeftButton.setScale(0.35,0.35);
        hoveredLeftButton.setPosition(500, 900);

        sf::FloatRect rect = rightButton.getGlobalBounds();
        rightButton.setTexture(this->data->assetManager.GetTexture("Right button"));
        rightButton.setScale(0.35,0.35);
        rightButton.setPosition(SCREEN_WIDTH - 500 + rect.width, 900);

        hoveredRightButton.setTexture(this->data->assetManager.GetTexture("Right Hovered"));
        hoveredRightButton.setScale(0.35,0.35);
        hoveredRightButton.setPosition(SCREEN_WIDTH - 500 + rect.width, 900);

        //The buttons in an array
        pressedButtons[0] = hoveredLeftButton;
        pressedButtons[1] = hoveredRightButton;
        buttons[0] = leftButton;
        buttons[1] = rightButton;

        clockJoystick.restart();
    }

    void LevelSelectState::HandleInput() {
        sf::Event event;

        while (data->window.pollEvent(event)) {
            if (event.type == sf::Event::MouseMoved) isMouseMoved = true;

            //If player uses mouse on the leftbutton, a new level-image will appear
            if (event.type == sf::Event::MouseButtonPressed) {
                if (data->inputManager.IsSpriteClicked(buttons[0], sf::Mouse::Button::Left, data->window)) {
                    isHoveredLeft = true;
                    if (levelChoice == 0) levelChoice = levels.size() - 1;
                    else levelChoice--;
                }
            //If player uses mouse on the rightbutton, a new level-image will appear
                if (data->inputManager.IsSpriteClicked(buttons[1], sf::Mouse::Button::Left, data->window)) {
                    isHoveredRight = true;
                    if (levelChoice == levels.size() - 1) levelChoice = 0;
                    else levelChoice++;
                }
            }

            //Buttons will not hover when not pressed
            if (event.type == sf::Event::MouseButtonReleased) {
                isHoveredLeft = false;
                isHoveredRight = false;
            }

            //Removes state when ESCAPE is pressed
            if (event.key.code == sf::Keyboard::Escape) data->stateMachine.RemoveState();

            if (event.type == sf::Event::KeyPressed) {

                //If ENTER: Go to gamestate
                if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) GoToGameState();

                //If player press left, a new level-image will appear
                if (event.key.code == sf::Keyboard::Left) {
                    isHoveredLeft = true;
                    if (levelChoice == 0) levelChoice = levels.size() - 1;
                    else levelChoice--;
                }
                //If player press right, a new level-image will appear
                if (event.key.code == sf::Keyboard::Right) {
                    isHoveredRight = true;
                    if (levelChoice == levels.size() - 1) levelChoice = 0;
                    else levelChoice++;
                }
            }
            //Buttons will not hover when not pressed
            if (event.type == sf::Event::KeyReleased) {
                isHoveredLeft = false;
                isHoveredRight = false;
            }
            //If joystick moved right, change picture
            if (event.type == sf::Event::JoystickMoved) {
                if (JOYSTICK_RIGHT){
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed > minTimeJoystick) {
                        lastTimePressed = clockJoystick.getElapsedTime().asMilliseconds();
                        isHoveredRight = true;
                        if (levelChoice == levels.size() - 1) levelChoice = 0;
                        else levelChoice++;
                    }
                }
                //If joystick moved left, change picture
                if (JOYSTICK_LEFT){
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed > minTimeJoystick) {
                        lastTimePressed = clockJoystick.getElapsedTime().asMilliseconds();
                        isHoveredLeft = true;
                        if (levelChoice == 0) levelChoice = levels.size() - 1;
                        else levelChoice--;
                    }
                }
                //If not left or right, no hovered buttons
                if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > -30 && sf::Joystick::getAxisPosition(0, sf::Joystick::X) < 30){
                    isHoveredRight = false;
                    isHoveredLeft = false;
                }
            }
            //If A pressed go to gamestate, if B pressed, go back
            if (event.type == sf::Event::JoystickButtonPressed) {
                if(JOYSTICK1_A) GoToGameState();
                if(JOYSTICK1_B) data->stateMachine.RemoveState();
            }
        }

        // Set levelName string and position
        if(isLevelOneSelected) levelName.setString("Bright Forest");
        else if(isLevelTwoSelected) levelName.setString("Kitchen Mania");
        else if(isLevelThreeSelected) levelName.setString("Winter Wonderland");
        textRect = levelName.getGlobalBounds();
        levelName.setPosition((SCREEN_WIDTH/2) - textRect.width/2, 900);

        isLevelOneSelected=levelChoice==0;
        isLevelTwoSelected=levelChoice==1;
        isLevelThreeSelected=levelChoice==2;
        // Decide which buttons should be visible by bools
        buttons[0].setColor(isHoveredLeft ? sf::Color::Transparent : sf::Color::White);
        buttons[1].setColor(isHoveredRight ? sf::Color::Transparent : sf::Color::White);
        pressedButtons[0].setColor(isHoveredLeft ? sf::Color::White : sf::Color::Transparent);
        pressedButtons[1].setColor(isHoveredRight ? sf::Color::White : sf::Color::Transparent);

        isMouseMoved = false;
    }


    void LevelSelectState::Update(float delta) {}

    void LevelSelectState::Draw(float delta) {
        data->window.clear();

        //Draw background and level-images
        data->window.draw(levelBackground);
        data->window.draw(levels[levelChoice]);

        //Draw the buttons
        if(!isHoveredLeft || !isHoveredRight) for(const auto &it: buttons) data->window.draw(it.second);
        if(isHoveredLeft || isHoveredRight) for(const auto &it: pressedButtons) data->window.draw(it.second);

        //Draw levelname
        data->window.draw(levelName);

        data->window.display();
    }

    //When you have chosen a level: music stops, and you'll be sent to gamestate
    void LevelSelectState::GoToGameState() {
        data->levelChoice = (int)levelChoice;

        data->music->stop();
        data->isMusicPlaying = false;

        data->stateMachine.AddState(StateRef(new GameState(this->data, this->singleplayer)));
    }
}