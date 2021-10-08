#include <iostream>
#include <plog/Log.h>
#include "settings_state.h"
#include "DEFINITIONS.h"
#include "menu_state.h"

namespace Kjeledyr {

    SettingsState::SettingsState(GameDataRef data) : data(data) {
    }
    //Adds in all assets used in Setttings-menu
    void SettingsState::Init() {
        background.setTexture(this->data->assetManager.GetTexture("Settings Menu"));

        controllerGuide.setTexture(this->data->assetManager.GetTexture("Controller Guide"));
        controllerGuide.setPosition(360,400);
        controllerGuide.setScale(0.95, 0.90);

        musicBar.setTexture(this->data->assetManager.GetTexture("Volume Bar"));
        musicBar.setPosition(698, 181);
        musicSlider.setFillColor(sf::Color(119, 248, 134));
        musicSlider.setSize(sf::Vector2f(musicWidth, volumeHeigth));
        musicSlider.setPosition(sliderX, 183);
        pressedButtons[0] = musicBar;

        VSyncText.setFont(this->data->assetManager.GetFont("Berlin Sans FB"));
        VSyncText.setPosition(1000, 270);
        VSyncText.setCharacterSize(60);
        VSyncText.setString(on);

        leftButton.setTexture(this->data->assetManager.GetTexture("Left button"));
        leftButton.setScale(0.15, 0.15);
        leftButton.setPosition(760, 295);
        buttons[1] = leftButton;
        leftHoveredButton.setTexture(this->data->assetManager.GetTexture("Left Hovered"));
        leftHoveredButton.setScale(0.15, 0.15);
        leftHoveredButton.setPosition(760, 295);
        pressedButtons[1] = leftHoveredButton;

        rightButton.setTexture(this->data->assetManager.GetTexture("Right button"));
        rightButton.setScale(0.15, 0.15);
        rightButton.setPosition(1300, 295);
        buttons[2] = rightButton;
        rightHoveredButton.setTexture(this->data->assetManager.GetTexture("Right Hovered"));
        rightHoveredButton.setScale(0.15, 0.15);
        rightHoveredButton.setPosition(1300, 295);
        pressedButtons[2] = rightHoveredButton;

        backButton.setTexture(this->data->assetManager.GetTexture("Settings Back Button"));
        backButton.setPosition(1705, 30);
        buttons[3] = backButton;
        backButtonPressed.setTexture(this->data->assetManager.GetTexture("Settings Back Pressed Button"));
        backButtonPressed.setPosition(1705, 30);
        pressedButtons[3] = backButtonPressed;

        soundButton.setTexture(this->data->assetManager.GetTexture("Sound Button"));
        soundButton.setPosition(1805, 30);
        soundButtonPressed.setTexture(this->data->assetManager.GetTexture("Sound Button Pressed"));
        soundButtonPressed.setPosition(1805, 30);

        muteButton.setTexture(this->data->assetManager.GetTexture("Mute Button"));
        muteButton.setPosition(1805, 30);
        muteButtonPressed.setTexture(this->data->assetManager.GetTexture("Mute Button Pressed"));
        muteButtonPressed.setPosition(1805, 30);
        LOGI<<"Settings Initialized";
    }
    //Handles the navigation
    void SettingsState::HandleInput() {
        sf::Event event;

        if(JOYSTICK1_B)data->stateMachine.AddState(StateRef(new MenuState(this->data)));
        while(data->window.pollEvent(event)){
            if(event.type == sf::Event::Closed) data->window.close();
            if(event.type == sf::Event::MouseMoved) mouseMoved = true;

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Up) up = true;
                if(event.key.code == sf::Keyboard::Down) down = true;
                if(event.key.code == sf::Keyboard::Escape) {
                    LOGI<<"Settings to Menu";
                    data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                }

                if(event.key.code == sf::Keyboard::Left) {
                    if (isMusicSelected){
                        if(data->volumeMusic > 0) musicWidth -= 25;
                    }
                }

                if(event.key.code == sf::Keyboard::Right) {
                    if (isMusicSelected){
                        if(data->volumeMusic < 100) musicWidth += 25;
                    }

                }

                if(event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
                    if(isSoundSelected){
                        data->isSoundOn = !data->isSoundOn;
                        if(!data->isSoundOn)data->music->pause();
                        else data->music->play();
                    }

                    if(isMenuSelected){
                        data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                    }
                    if(isLeftSelected || isRightSelected){
                        if(off.compare(VSyncText.getString())==0){
                            VSyncText.setString(on);
                            data->window.setVerticalSyncEnabled(true);
                            LOGI<<"V-Sync set to ON";
                        }
                        if(on.compare(VSyncText.getString())==0){
                            VSyncText.setString(off);
                            data->window.setVerticalSyncEnabled(false);
                            LOGI<<"V-Sync set to OFF";
                        }
                    }
                }
            }

            if(event.type == sf::Event::MouseButtonPressed){
                if(data->inputManager.IsSpriteClicked(musicBar, sf::Mouse::Button::Left, data->window)){
                    sf::Vector2i tmp = sf::Mouse::getPosition();
                    musicWidth = tmp.x;
                }

                if(data->inputManager.IsSpriteClicked(backButton, sf::Mouse::Button::Left, data->window)){
                    data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                }

                if(data->inputManager.IsSpriteClicked(leftButton, sf::Mouse::Button::Left, data->window) ||
                        data->inputManager.IsSpriteClicked(rightButton, sf::Mouse::Button::Left, data->window)){
                    if(off.compare(VSyncText.getString())==0){
                        VSyncText.setString(on);
                        data->window.setVerticalSyncEnabled(true);
                        LOGI<<"V-Sync set to ON";
                    }
                    if(on.compare(VSyncText.getString())==0){
                        VSyncText.setString(off);
                        data->window.setVerticalSyncEnabled(false);
                        LOGI<<"V-Sync set to OFF";
                    }
                }


                if(data->inputManager.IsSpriteClicked(soundButton, sf::Mouse::Button::Left, data->window)){
                    data->isSoundOn = !data->isSoundOn;
                    if(!data->isSoundOn)data->music->pause();
                    else data->music->play();
                }
            }
        }

        if(data->isSoundOn) {
            buttons[4] = soundButton;
            pressedButtons[4] = soundButtonPressed;
        }
        else {
            buttons[4] = muteButton;
            pressedButtons[4] = muteButtonPressed;
        }

        hoveredSprite = data->inputManager.GetCurrentSprite(pressedButtons, hoveredSprite, mouseMoved, up, down, data->window);


        isMusicSelected = hoveredSprite == 0;
        isLeftSelected = hoveredSprite == 1;
        isRightSelected = hoveredSprite == 2;
        isMenuSelected = hoveredSprite == 3;
        isSoundSelected = hoveredSprite == 4;

        buttons[1].setColor(isLeftSelected ? sf::Color::Transparent : sf::Color::White);
        buttons[2].setColor(isRightSelected ? sf::Color::Transparent : sf::Color::White);
        buttons[3].setColor(isMenuSelected ? sf::Color::Transparent : sf::Color::White);
        buttons[4].setColor(isSoundSelected ? sf::Color::Transparent : sf::Color::White);

        musicSlider.setFillColor(isMusicSelected ? sf::Color(153, 224, 246)  : sf::Color::Green);
        pressedButtons[1].setColor(isLeftSelected ? sf::Color::White : sf::Color::Transparent);
        pressedButtons[2].setColor(isRightSelected ? sf::Color::White : sf::Color::Transparent);
        pressedButtons[3].setColor(isMenuSelected ? sf::Color::White : sf::Color::Transparent);
        pressedButtons[4].setColor(isSoundSelected ? sf::Color::White : sf::Color::Transparent);

        mouseMoved = false;
        up = false;
        down = false;
        left = false;
    }
    //Changes the volume
    void SettingsState::Update(float delta) {
        data->volumeMusic = Map(musicWidth - sliderX, volumeMin, volumeMax, 0, 100);
        data->music->setVolume(data->volumeMusic);
        musicSlider.setSize(sf::Vector2f((musicWidth - sliderX), volumeHeigth));
    }
    //Draws everything
    void SettingsState::Draw(float delta) {
        data->window.clear();
        data->window.draw(background);

        for(auto &it: buttons) data->window.draw(it.second);
        for(auto &it: pressedButtons) data->window.draw(it.second);

        data->window.draw(musicSlider);
        data->window.draw(musicBar);
        data->window.draw(VSyncText);
        data->window.draw(controllerGuide);

        data->window.display();
    }

    long SettingsState::Map(long x, long in_min, long in_max, long out_min, long out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
}