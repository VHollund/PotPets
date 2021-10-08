#include "menu_state.h"
#include "game_state.h"
#include "highscore_state.h"
#include "settings_state.h"
#include "charselect_state.h"
#include <plog/Log.h>

namespace Kjeledyr{

    MenuState::MenuState(GameDataRef data) : data(data){}

    void MenuState::Init() {

        background.setTexture(this->data->assetManager.GetTexture("Menu Background"));
        title.setTexture(this->data->assetManager.GetTexture("Title"));
        sf::FloatRect rect = title.getGlobalBounds();
        title.setOrigin(rect.left + rect.width/2, rect.top + rect.height/2);
        title.setPosition(SCREEN_WIDTH/2, 300);

        playButton.setTexture(this->data->assetManager.GetTexture("Play Button"));
        playButton.setPosition(750, 450);
        buttons[0] = playButton;
        playButtonPressed.setTexture(this->data->assetManager.GetTexture("Play Button Pressed"));
        playButtonPressed.setPosition(750, 450);
        pressedButtons[0] = playButtonPressed;

        highScoreButton.setTexture(this->data->assetManager.GetTexture("Highscore Button"));
        highScoreButton.setPosition(750, 590);
        buttons[1] = highScoreButton;
        highScoreButtonPressed.setTexture(this->data->assetManager.GetTexture("Highscore Button Pressed"));
        highScoreButtonPressed.setPosition(750, 590);
        pressedButtons[1] = highScoreButtonPressed;

        exitButton.setTexture(this->data->assetManager.GetTexture("Exit Button"));
        exitButton.setPosition(750, 730);
        buttons[2] = exitButton;
        exitButtonPressed.setTexture(this->data->assetManager.GetTexture("Exit Button Pressed"));
        exitButtonPressed.setPosition(750, 730);
        pressedButtons[2] = exitButtonPressed;

        settingsButton.setTexture(this->data->assetManager.GetTexture("Settings Button"));
        settingsButton.setPosition(1705, 30);
        buttons[3] = settingsButton;
        settingsButtonPressed.setTexture(this->data->assetManager.GetTexture("Settings Button Pressed"));
        settingsButtonPressed.setPosition(1705, 31);
        pressedButtons[3] = settingsButtonPressed;

        soundButton.setTexture(this->data->assetManager.GetTexture("Sound Button"));
        soundButton.setPosition(1805, 30);
        soundButtonPressed.setTexture(this->data->assetManager.GetTexture("Sound Button Pressed"));
        soundButtonPressed.setPosition(1805, 30);

        muteButton.setTexture(this->data->assetManager.GetTexture("Mute Button"));
        muteButton.setPosition(1805, 30);
        muteButtonPressed.setTexture(this->data->assetManager.GetTexture("Mute Button Pressed"));
        muteButtonPressed.setPosition(1805, 30);

        data->music = data->assetManager.GetMusic("Music");

        backgroundObjects = new backgroundAnimations(0);

        if(!data->isMusicPlaying && data->isSoundOn){
            data->music->play();
            data->isMusicPlaying = true;
        }
        LOGI<<"Menu State Initialized";
    }

    // Handles different events and how we select options in menu
    void MenuState::HandleInput() {
        sf::Event event;

        while(data->window.pollEvent(event)){

            if(event.type == sf::Event::Closed) data->window.close();

            if(event.type == sf::Event::MouseMoved) mouseMoved = true;

            if(event.type == sf::Event::MouseButtonPressed){
                if(data->inputManager.IsSpriteClicked(pressedButtons[0], sf::Mouse::Button::Left, data->window)){
                    LOGI<<"Menu to CharSelectState";
                    data->stateMachine.AddState(StateRef(new CharSelectState(this->data)));
                }
                if(data->inputManager.IsSpriteClicked(pressedButtons[1], sf::Mouse::Button::Left, data->window)){
                    LOGI<<"Menu to Highscore";
                    data->stateMachine.AddState(StateRef(new HighscoreState(this->data)));
                }

                if(data->inputManager.IsSpriteClicked(pressedButtons[2], sf::Mouse::Button::Left, data->window)){
                    data->music->stop();
                    data->window.close();
                }
                if(data->inputManager.IsSpriteClicked(pressedButtons[3], sf::Mouse::Button::Left, data->window)){
                    LOGI<<"Menu to SettingState";
                    data->stateMachine.AddState(StateRef(new SettingsState(this->data)));
                }
                if(data->inputManager.IsSpriteClicked(pressedButtons[4], sf::Mouse::Button::Left, data->window)){
                    data->isSoundOn = !data->isSoundOn;
                    if(!data->isSoundOn)data->music->pause();
                    else data->music->play();
                }
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Up) up = true;
                if(event.key.code == sf::Keyboard::Down) down = true;
                if(event.key.code == sf::Keyboard::Escape) data->window.close();

                // Handles enter button
                if(event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
                    if(isPlaySelected) {
                        LOGI<<"Menu to CharSelectState";
                        data->stateMachine.AddState(StateRef(new CharSelectState(this->data)));
                    }
                    if(isHighscoreSelected) {
                        LOGI<<"Menu to Highscore";
                        data->stateMachine.AddState(StateRef(new HighscoreState(this->data)));
                    }
                    if(isExitSelected) {
                        data->music->stop();
                        data->window.close();
                    }
                    if(isSettingsSelected) {
                        LOGI<<"Menu to SettingState";
                        data->stateMachine.AddState(StateRef(new SettingsState(this->data)));
                    }
                    if(isSoundSelected){
                        data->isSoundOn = !data->isSoundOn;
                        if(!data->isSoundOn)data->music->pause();
                        else data->music->play();
                    }
                }
            }

            if(event.type == sf::Event::JoystickMoved){
                if(JOYSTICK_UP) up = true;
                if(JOYSTICK_DOWN) down = true;
            }

            if(event.type == sf::Event::JoystickButtonPressed){
                if(JOYSTICK1_A){
                    if(isPlaySelected) {
                        LOGI<<"Menu to CharSelectState";
                        data->stateMachine.AddState(StateRef(new CharSelectState(this->data)));
                    }
                    if(isHighscoreSelected) {
                        LOGI<<"Menu to Highscore";
                        data->stateMachine.AddState(StateRef(new HighscoreState(this->data)));
                    }
                    if(isExitSelected) {
                        data->music->stop();
                        data->window.close();
                    }
                    if(isSettingsSelected) {
                        LOGI<<"Menu to SettingState";
                        data->stateMachine.AddState(StateRef(new SettingsState(this->data)));
                    }
                    if(isSoundSelected){
                        data->isSoundOn = !data->isSoundOn;
                        if(!data->isSoundOn)data->music->pause();
                        else data->music->play();
                    }
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

        // Highlight hovered option and reset for next input
        hoveredSprite = data->inputManager.GetCurrentSprite(pressedButtons, hoveredSprite, mouseMoved, up, down,
                                                             data->window);

        isPlaySelected = hoveredSprite == 0;
        isHighscoreSelected = hoveredSprite == 1;
        isExitSelected = hoveredSprite == 2;
        isSettingsSelected = hoveredSprite == 3;
        isSoundSelected = hoveredSprite == 4;

        buttons[0].setColor(isPlaySelected ? sf::Color::Transparent : sf::Color::White);
        buttons[1].setColor(isHighscoreSelected ? sf::Color::Transparent : sf::Color::White);
        buttons[2].setColor(isExitSelected ? sf::Color::Transparent : sf::Color::White);
        buttons[3].setColor(isSettingsSelected ? sf::Color::Transparent : sf::Color::White);
        buttons[4].setColor(isSoundSelected ? sf::Color::Transparent : sf::Color::White);

        pressedButtons[0].setColor(isPlaySelected ? sf::Color::White : sf::Color::Transparent);
        pressedButtons[1].setColor(isHighscoreSelected ? sf::Color::White : sf::Color::Transparent);
        pressedButtons[2].setColor(isExitSelected ? sf::Color::White : sf::Color::Transparent);
        pressedButtons[3].setColor(isSettingsSelected ? sf::Color::White : sf::Color::Transparent);
        pressedButtons[4].setColor(isSoundSelected ? sf::Color::White : sf::Color::Transparent);

        mouseMoved = false;
        up = false;
        down = false;
    }

    void MenuState::Update(float delta) {
        backgroundObjects->tick();
    }

    void MenuState::Draw(float delta) {
        data->window.clear();

        data->window.draw(background);

        for (int i = 0; i < backgroundObjects->GetAllObjectsSize(); ++i) data->window.draw(backgroundObjects->GetObject(i).DrawSprite());

        data->window.draw(title);

        for(const auto &it: pressedButtons) data->window.draw(it.second);
        for(const auto &it: buttons) data->window.draw(it.second);

        data->window.display();
    }

}
