#include <iostream>
#include <fstream>
#include <plog/Log.h>
#include "game_over_state.h"
#include "menu_state.h"
#include "highscore_state.h"

namespace Kjeledyr{

    GameOverState::GameOverState(GameDataRef data, int score, int winner, bool singleplayer)  : data(data), score(score), winner(winner), singlePlayer(singleplayer){
    }

    void GameOverState::Init() {
        font = data->assetManager.GetFont("Berlin Sans FB");

        gameOverBackground.setTexture(this->data->assetManager.GetTexture("Game Over Background"));
        newHighscoreBackground.setTexture(this->data->assetManager.GetTexture("New Highscore Background"));

        menuButton.setTexture(this->data->assetManager.GetTexture("Menu button"));
        menuButton.setPosition((SCREEN_WIDTH / 2) - 570, 775);
        menuButtonPressed.setTexture(this->data->assetManager.GetTexture("Menu button pressed"));
        menuButtonPressed.setPosition((SCREEN_WIDTH / 2) - 570, 775);
        menuOptions[0] = menuButtonPressed;

        highScoreButton.setTexture(this->data->assetManager.GetTexture("Highscore button"));
        highScoreButton.setPosition((SCREEN_WIDTH / 2) + 60, 775);
        highScoreButtonPressed.setTexture(this->data->assetManager.GetTexture("Highscore button pressed"));
        highScoreButtonPressed.setPosition((SCREEN_WIDTH / 2) + 60, 775);
        menuOptions[1] = highScoreButtonPressed;

        okButton.setTexture(this->data->assetManager.GetTexture("OK"));
        okButton.setPosition(1197, 750);
        okButtonPressed.setTexture(this->data->assetManager.GetTexture("OK pressed"));
        okButtonPressed.setPosition(1197, 750);

        scoreString.setFont(font);
        scoreString.setCharacterSize(200);
        scoreString.setColor(sf::Color::White);
        scoreString.setString(std::to_string(score) + " pts");
        textRect = scoreString.getGlobalBounds();
        scoreString.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
        scoreString.setPosition(SCREEN_WIDTH/2, 520);

        max10Chars.setFont(font);
        max10Chars.setCharacterSize(60);
        max10Chars.setColor(sf::Color(226, 226, 226));
        max10Chars.setString("Joystick: Press Y");
        textRect = max10Chars.getGlobalBounds();
        max10Chars.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
        max10Chars.setPosition(SCREEN_WIDTH/2 - 125, 820);

        previewCh.setFont(font);
        previewCh.setCharacterSize(60);
        previewCh.setColor(sf::Color(226, 226, 226));
        previewCh.setString(currentCh);
        previewCh.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
        previewCh.setPosition(SCREEN_WIDTH/2 - 125, 820);

        name.setFont(font);
        name.setCharacterSize(60);
        name.setColor(sf::Color::Black);
        name.setString("");
        name.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
        name.setPosition(SCREEN_WIDTH/2 - 125, 820);

        LoadHead();

        LoadAlphabet();
        currentCh = alphabet[0];
        LoadHighscores();
        if(singlePlayer) newHighscore = CheckForHighscore(data->highscoresSP, score);
        else newHighscore = CheckForHighscore(data->highscoresMP, score);
    }

    void GameOverState::HandleInput() {
        sf::Event event;

        while(data->window.pollEvent(event)){
            if(event.type == sf::Event::Closed) data->window.close();

            if(newHighscore){
                if (event.type == sf::Event::TextEntered) {
                    // Only allow ASCII numbers, letters and backspace
                    if ((event.text.unicode > 47 && event.text.unicode < 58) ||
                        (event.text.unicode > 64 && event.text.unicode < 91) ||
                        (event.text.unicode > 96 && event.text.unicode < 123)) {
                        if (nameEntered.size() < 10) {
                            nameEntered += static_cast<char>(event.text.unicode);
                            name.setString(nameEntered);
                        }
                    }

                    // Allow backspace
                    if (event.text.unicode == 8 && !name.getString().isEmpty()) {
                        nameEntered.pop_back();
                        name.setString(nameEntered);
                    }
                }

                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::Left) isOKSelected = false;
                    if(event.key.code == sf::Keyboard::Right) isOKSelected = true;
                    if(event.key.code == sf::Keyboard::Return && !name.getString().isEmpty() && !charSelect){
                        if (singlePlayer) {
                            data->highscoresSP[score] = nameEntered;
                            SaveHighscore(data->highscoresSP);
                        } else {
                            data->highscoresMP[score] = nameEntered;
                            SaveHighscore(data->highscoresMP);
                        }
                        newHighscore = false;
                    }
                }
            }

            else {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                    if (event.key.code == sf::Keyboard::Left) left = true;
                    if (event.key.code == sf::Keyboard::Right) right = true;
                    if (event.key.code == sf::Keyboard::Return) {
                        if (hoveredSprite == 0) data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                        if (hoveredSprite == 1) data->stateMachine.AddState(StateRef(new HighscoreState(this->data)));
                    }
                }
            }

            if(event.type == sf::Event::MouseMoved) mouseMoved = true;

            if(event.type == sf::Event::MouseButtonPressed){
                if(newHighscore) {
                    if (data->inputManager.IsSpriteClicked(okButton, sf::Mouse::Button::Left, data->window)) {
                        if (!name.getString().isEmpty()) {
                            if(singlePlayer) {
                                data->highscoresSP[score] = nameEntered;
                                SaveHighscore(data->highscoresSP);
                            } else {
                                data->highscoresMP[score] = nameEntered;
                                SaveHighscore(data->highscoresMP);
                            }
                            newHighscore = false;
                        }
                    }
                } else {
                    if (data->inputManager.IsSpriteClicked(menuOptions[0], sf::Mouse::Button::Left, data->window)) {
                        data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                    }

                    if (data->inputManager.IsSpriteClicked(menuOptions[1], sf::Mouse::Button::Left, data->window)) {
                        data->stateMachine.AddState(StateRef(new HighscoreState(this->data)));
                    }
                }
            }

            if(event.type == sf::Event::JoystickMoved){
                if(!newHighscore) {
                    if (JOYSTICK_RIGHT) right = true;
                    if (JOYSTICK_LEFT) left = true;
                }

                if(newHighscore && charSelect){
                    if(JOYSTICK_UP){
                        if(currentKey == 0) {
                            currentKey = alphaEnd;
                            currentCh = alphabet[currentKey];
                        } else {
                            currentKey--;
                            currentCh = alphabet[currentKey];
                        }
                        previewCh.setString(currentCh);
                    }

                    if(JOYSTICK_DOWN){
                        if(currentKey == alphaEnd) {
                            currentKey = 0;
                            currentCh = alphabet[currentKey];
                        } else {
                            currentKey++;
                            currentCh = alphabet[currentKey];
                        }
                        previewCh.setString(currentCh);
                    }


                    if(JOYSTICK_RIGHT && !nameEntered.empty()) isOKSelected = true;
                    if(JOYSTICK_LEFT) isOKSelected = false;
                }
            }

            if(event.type == sf::Event::JoystickButtonPressed){

                // Activate name selection for joystick
                if(sf::Joystick::isButtonPressed(winner, 4)){
                    charSelect = true;
                    currentCh = alphabet[0];
                    previewCh.setString(currentCh);
                }

                // Handle X button
                if(sf::Joystick::isButtonPressed(winner, 2)){
                    if(!newHighscore){
                        if(hoveredSprite == 0) data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                        if(hoveredSprite == 1) data->stateMachine.AddState(StateRef(new HighscoreState(this->data)));
                    }

                    // If joystick name selection is active
                    if(charSelect){
                        name.setString(name.getString() + currentCh);
                        previewCh.move(35, 0);
                        currentKey = 0;
                        currentCh = alphabet[currentKey];
                        previewCh.setString(currentCh);
                    }

                    // Save highscore
                    if(isOKSelected){
                        if(singlePlayer) {
                            data->highscoresSP[score] = name.getString();
                            SaveHighscore(data->highscoresSP);
                        } else {
                            data->highscoresMP[score] = name.getString();
                            SaveHighscore(data->highscoresMP);
                        }

                        charSelect = false;
                        newHighscore = false;
                    }
                }

                // Erase last character

                if(sf::Joystick::isButtonPressed(winner, 1) && charSelect){
                    nameEntered = name.getString();
                    nameEntered.pop_back();
                    name.setString(nameEntered);
                    previewCh.move(-35, 0);
                    currentKey = 0;
                    currentCh = alphabet[currentKey];
                    previewCh.setString(currentCh);
                }
            }
        }

        hoveredSprite = data->inputManager.GetCurrentSprite(menuOptions, hoveredSprite, mouseMoved, left, right,
                                                             data->window);

        isMenuSelected = hoveredSprite == 0;
        isHighscoreSelected = hoveredSprite == 1;

        menuOptions[0].setColor(isMenuSelected ? sf::Color::White : sf::Color::Transparent);
        menuOptions[1].setColor(isHighscoreSelected ? sf::Color::White : sf::Color::Transparent);

        mouseMoved = false;
        left = false;
        right = false;
    }

    void GameOverState::Update(float delta) {
    }

    void GameOverState::Draw(float delta) {
        data->window.clear();

        if(newHighscore){
            data->window.draw(newHighscoreBackground);
            data->window.draw(scoreString);

            if(isOKSelected) data->window.draw(okButtonPressed);
            else data->window.draw(okButton);

            if(name.getString().isEmpty() && !charSelect) data->window.draw(max10Chars);
            else data->window.draw(name);

            data->window.draw(head);

            if(charSelect){
                data->window.draw(previewCh);
                data->window.draw(name);
            }

        } else {
            data->window.draw(gameOverBackground);
            data->window.draw(scoreString);
            for(const auto &buttons: menuOptions) data->window.draw(buttons.second);
            if(isMenuSelected) data->window.draw(highScoreButton);
            if(isHighscoreSelected) data->window.draw(menuButton);
        }


        data->window.display();
    }

    /**
     * Checks if the game score is a highscore.
     *
     * @param highscore global map containing highscores
     * @param score score to be compared to highscores
     * @return true if highscore, false if not
     */
    bool GameOverState::CheckForHighscore(std::map<int, std::string> highscore, int score) {
        if(highscore.size() < 10) return true;

        for (auto &it: highscore) {
            if (score > it.first) {
                return true;
            }
        }

        return false;
    }

    /* Saves content of global highscore maps into the corresponding text files.
     * Reverse iterates through maps to get highest to lowest score.
     * Erases the lowest score if highscore list is full. */
    void GameOverState::SaveHighscore(std::map<int, std::string> highscores) {
        std::fstream highscoreFile;
        if(singlePlayer) highscoreFile.open("HighscoresSP.txt");
        else highscoreFile.open("HighscoresMP.txt");

        LOGE_IF(!highscoreFile) << "Failed to open the highscore file!";

        std::string score;
        std::string name;

        for(auto it = highscores.rbegin(); it != highscores.rend(); it++){
            if(highscores.size() > 10){
                highscores.erase(highscores.begin());
            }

            score = std::to_string(it->first);
            name = it->second;

            highscoreFile << score << std::endl;
            highscoreFile << name << std::endl;
        }

        highscoreFile.ignore();
        highscoreFile.close();
        LOGI << "Highscore file saved.";
    }


    /* If singlePlayer is true, load content of HighscoresSP.txt into corresponding global map.
     * If singlePlayer is false, load content of HighscoresMP.txt into corresponding global map. */
    void GameOverState::LoadHighscores(){
        std::ifstream highscores;
        if(singlePlayer) {
            highscores.open("HighscoresSP.txt");
            LOGI << "Singleplayer highscore loaded!";
        }
        else {
            highscores.open("HighscoresMP.txt");
            LOGI << "Multiplayer highscore loaded";
        }

        LOGE_IF(!highscores) << "Failed to open the highscore file!";

        std::string score;
        std::string name;

        while(highscores.peek() != std::ifstream::traits_type::eof()){
            std::getline(highscores, score);
            std::getline(highscores, name);
            if(singlePlayer) data->highscoresSP[std::stoi(score)] = name;
            else data->highscoresMP[std::stoi(score)] = name;
        }

        highscores.close();
    }

    void GameOverState::LoadAlphabet(){
        int key = 0;
        for(char ch = 'a'; ch <= 'z'; ch++){
            alphabet[key] = ch;
            key++;
        }
        for(char ch = 'A'; ch <= 'Z'; ch++){
            alphabet[key] = ch;
            key++;
        }
        for(char ch = '0'; ch <= '9'; ch++){
            alphabet[key] = ch;
            key++;
        }
        alphaEnd = key - 1;
    }

    void GameOverState::LoadHead() {
        head.setTexture(*SetHeadTexture(data->chosenSprite[winner]).getTexture());
        head.setPosition(660,650);
    }

    sf::Sprite GameOverState::SetHeadTexture(int spriteOffSet) {
        sf::Sprite temp;
        if(spriteOffSet==0) temp.setTexture(data->assetManager.GetTexture("BunnyHead"));
        if(spriteOffSet==1) temp.setTexture(data->assetManager.GetTexture("CatHead"));
        if(spriteOffSet==2) temp.setTexture(data->assetManager.GetTexture("DogHead"));
        if(spriteOffSet==3) temp.setTexture(data->assetManager.GetTexture("PigHead"));
        return temp;
    }

}