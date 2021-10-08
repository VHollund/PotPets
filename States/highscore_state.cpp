#include "highscore_state.h"
#include "DEFINITIONS.h"
#include "menu_state.h"

#include <fstream>
#include <iostream>
#include <plog/Log.h>


namespace Kjeledyr{

    HighscoreState::HighscoreState(GameDataRef data) : data(data){}

    void HighscoreState::Init(){
        background.setTexture(this->data->assetManager.GetTexture("Highscore State Background"));

        backButton.setTexture(this->data->assetManager.GetTexture("Back Button"));
        backButton.setPosition(30, 30);
        backPressedButton.setTexture(this->data->assetManager.GetTexture("Back Pressed"));
        backPressedButton.setPosition(30, 30);
        menuOptions[0] = backPressedButton;

        spButton.setTexture(this->data->assetManager.GetTexture("Singleplayer Button"));
        spButton.setPosition(538, 930);
        spPressedButton.setTexture(this->data->assetManager.GetTexture("Singleplayer Pressed"));
        spPressedButton.setPosition(541, 930);
        menuOptions[1] = spPressedButton;

        mpButton.setTexture(this->data->assetManager.GetTexture("Multiplayer Button"));
        mpButton.setPosition(960, 930);
        mpPressedButton.setTexture(this->data->assetManager.GetTexture("Multiplayer Pressed"));
        mpPressedButton.setPosition(960, 927);
        menuOptions[2] = mpPressedButton;

        font = data->assetManager.GetFont("Berlin Sans FB");

        rank.setFont(font);
        rank.setCharacterSize(40);
        rank.setColor(sf::Color::White);

        name.setFont(font);
        name.setCharacterSize(40);
        name.setColor(sf::Color::White);

        score.setFont(font);
        score.setCharacterSize(40);
        score.setColor(sf::Color::White);

        LoadHighscores();
        LoadHighscoreInfo(data->highscoresSP, data->highscoresMP);
    }

    void HighscoreState::HandleInput() {
        sf::Event event;

        while(data->window.pollEvent(event)){
            if(event.type == sf::Event::Closed) {
                data->window.close();
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape) data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                if(event.key.code == sf::Keyboard::Left) left = true;
                if(event.key.code == sf::Keyboard::Right) right = true;

                if(event.key.code == sf::Keyboard::Return){
                    if(hoveredSprite == 0) data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                }
            }

            if(event.type == sf::Event::JoystickMoved){
                if(JOYSTICK_RIGHT) right = true;
                if(JOYSTICK_LEFT) left = true;
            }

            if(event.type == sf::Event::JoystickButtonPressed){
                if(JOYSTICK1_A) {
                    if (hoveredSprite == 0) data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                }
                if(JOYSTICK1_B) data->stateMachine.AddState(StateRef(new MenuState(this->data)));
            }

            if(event.type == sf::Event::MouseMoved) mouseMoved = true;

            if(event.type == sf::Event::MouseButtonPressed){
                if(data->inputManager.IsSpriteClicked(backButton, sf::Mouse::Button::Left, data->window)){
                    data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                }
            }

            hoveredSprite = data->inputManager.GetCurrentSprite(menuOptions, hoveredSprite, mouseMoved, left, right,
                                                                 data->window);

            isBackPressed = hoveredSprite == 0;
            isSingleplayerPressed = hoveredSprite == 1;
            isMultiplayerPressed = hoveredSprite == 2;

            menuOptions[0].setColor(isBackPressed ? sf::Color::White : sf::Color::Transparent);
            menuOptions[1].setColor(isSingleplayerPressed ? sf::Color::White : sf::Color::Transparent);
            menuOptions[2].setColor(isMultiplayerPressed ? sf::Color::White : sf::Color::Transparent);

            mouseMoved = false;
            left = false;
            right = false;
        }
    }

    void HighscoreState::Update(float delta){

    }

    void HighscoreState::Draw(float delta) {
        data->window.clear();

        data->window.draw(background);
        for(const auto &pressedButtons: menuOptions) data->window.draw(pressedButtons.second);

        if(!isBackPressed) data->window.draw(backButton);
        if(!isSingleplayerPressed) data->window.draw(spButton);

        if(isSingleplayerPressed || isBackPressed){
            for(auto rank: SPranks) data->window.draw(rank);
            for(auto names: SPnames) data->window.draw(names);
            for(auto scores: SPscores) data->window.draw(scores);
        }

        if(isMultiplayerPressed){
            for(auto rank: MPranks) data->window.draw(rank);
            for(auto names: MPnames) data->window.draw(names);
            for(auto scores: MPscores) data->window.draw(scores);
        } else data->window.draw(mpButton);

        data->window.display();
    }

    // Loads content of highscore files into global highscores map
    void HighscoreState::LoadHighscores(){

        if(data->highscoresSP.empty()) {
            std::string score;
            std::string name;

            std::ifstream SPhighscores;
            SPhighscores.open("HighscoresSP.txt");

            LOGE_IF(!SPhighscores) << "Failed to Load HighscoresSP!";

            while (SPhighscores.peek() != std::ifstream::traits_type::eof()) {
                std::getline(SPhighscores, score);
                std::getline(SPhighscores, name);
                data->highscoresSP[std::stoi(score)] = name;
            }

            SPhighscores.close();
        }

        if(data->highscoresMP.empty()) {
            std::string score;
            std::string name;

            std::ifstream MPhighscores;
            MPhighscores.open("HighscoresMP.txt");

            LOGE_IF(!MPhighscores) << "Failed to Load HighscoresMP!";

            while (MPhighscores.peek() != std::ifstream::traits_type::eof()) {
                std::getline(MPhighscores, score);
                std::getline(MPhighscores, name);
                data->highscoresMP[std::stoi(score)] = name;
            }

            MPhighscores.close();
        }
    }

    // Loads content in highscore map into appropriate vectors
    void HighscoreState::LoadHighscoreInfo(std::map<int, std::string> SPmap, std::map<int, std::string> MPmap) {
        int i = 0;
        int j = 0;

        for(auto it = SPmap.rbegin(); it != SPmap.rend(); it++){
            if(i < 10) {
                rank.setPosition(SCREEN_WIDTH / 2 - 370, (i + 3) * 70);
                rank.setString(std::to_string(i + 1) + ".");
                SPranks.emplace_back(rank);

                name.setPosition(SCREEN_WIDTH / 2 - 90, (i + 3) * 70);
                name.setString(it->second);
                SPnames.emplace_back(name);

                score.setPosition(SCREEN_WIDTH / 2 + 270, (i + 3) * 70);
                score.setString(std::to_string(it->first));
                SPscores.emplace_back(score);

                ++i;
            }
        }

        for(auto it = MPmap.rbegin(); it != MPmap.rend(); it++){
            if(j < 10) {
                rank.setPosition(SCREEN_WIDTH / 2 - 370, (j + 3) * 70);
                rank.setString(std::to_string(j + 1) + ".");
                MPranks.emplace_back(rank);

                name.setPosition(SCREEN_WIDTH / 2 - 90, (j + 3) * 70);
                name.setString(it->second);
                MPnames.emplace_back(name);

                score.setPosition(SCREEN_WIDTH / 2 + 270, (j + 3) * 70);
                score.setString(std::to_string(it->first));
                MPscores.emplace_back(score);

                ++j;
            }
        }

        LOGI << "Highscore info loaded";
    }
}