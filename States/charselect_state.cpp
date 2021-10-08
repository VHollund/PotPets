#include <DEFINITIONS.h>
#include <iostream>
#include <plog/Log.h>
#include "charselect_state.h"
#include "menu_state.h"
#include "game_state.h"
#include "levelselect_state.h"


namespace Kjeledyr {

    CharSelectState::CharSelectState(GameDataRef data) : data(data){}

    void CharSelectState::Init() {

        player1 = new players();
        player2 = new players();
        player3 = new players();
        player4 = new players();

        player1->controlID=0;

        allPlayers.emplace_back(player1);
        allPlayers.emplace_back(player2);
        allPlayers.emplace_back(player3);
        allPlayers.emplace_back(player4);

        takenChar[0] = false;
        takenChar[1] = false;
        takenChar[2] = false;
        takenChar[3] = false;

        for (int i = 0; i < 4; ++i) {
            lastTimePressed.push_back(0);
        }

        //Set the an id on every player 0,1,2,3
        int idcount = 0;
        for (auto player : allPlayers){
            player->id = idcount++;
        }

        clockJoystick.restart();

        //Load all the assets: Background and characters into a vector
        charBackground.setTexture(this->data->assetManager.GetTexture("Char State Background"));
        
        for(auto player : allPlayers){
            player->bunny.setTexture(this->data->assetManager.GetTexture("Bunny"));
            player->cat.setTexture(this->data->assetManager.GetTexture("Cat"));
            player->dog.setTexture(this->data->assetManager.GetTexture("Dog"));
            player->pig.setTexture(this->data->assetManager.GetTexture("Pig"));
        }

        player1->bunny.setPosition(400,40);
        player2->bunny.setPosition(1150,40);
        player3->bunny.setPosition(400,560);
        player4->bunny.setPosition(1150,560);

        player1->cat.setPosition(420,40);
        player2->cat.setPosition(1170,40);
        player3->cat.setPosition(420,560);
        player4->cat.setPosition(1170,560);

        player1->dog.setPosition(420,40);
        player2->dog.setPosition(1170,40);
        player3->dog.setPosition(420,560);
        player4->dog.setPosition(1170,560);

        player1->pig.setPosition(420,40);
        player2->pig.setPosition(1170,40);
        player3->pig.setPosition(420,560);
        player4->pig.setPosition(1170,560);

//###################################################################################################

        for(auto player : allPlayers){
            player->characters.push_back(player->bunny);
            player->characters.push_back(player->cat);
            player->characters.push_back(player->dog);
            player->characters.push_back(player->pig);
        }

//###################################################################################################

        //Loads buttons
        for(auto player : allPlayers){
            player->leftButton.setTexture(this->data->assetManager.GetTexture("Left button"));
            player->rightButton.setTexture(this->data->assetManager.GetTexture("Right button"));
            player->hoveredLeftButton.setTexture(this->data->assetManager.GetTexture("Hovered Left button"));
            player->hoveredRightButton.setTexture(this->data->assetManager.GetTexture("Hovered Right button"));
        }



        //Set position of buttons
        player1->leftButton.setPosition(240,420);
        player2->leftButton.setPosition(1000,420);
        player3->leftButton.setPosition(240,940);
        player4->leftButton.setPosition(1000,940);

        player1->rightButton.setPosition(850,420);
        player2->rightButton.setPosition(1610,420);
        player3->rightButton.setPosition(850,940);
        player4->rightButton.setPosition(1610,940);

        player1->hoveredLeftButton.setPosition(240,420);
        player2->hoveredLeftButton.setPosition(1000,420);
        player3->hoveredLeftButton.setPosition(240,940);
        player4->hoveredLeftButton.setPosition(1000,940);

        player1->hoveredRightButton.setPosition(850,420);
        player2->hoveredRightButton.setPosition(1610,420);
        player3->hoveredRightButton.setPosition(850,940);
        player4->hoveredRightButton.setPosition(1610,940);

        for(auto player : allPlayers){
            player->charSelect[0] = player->hoveredLeftButton;
            player->charSelect[1] = player->hoveredRightButton;
        }

        buttons.push_back(player1->leftButton);
        buttons.push_back(player1->rightButton);
        buttons.push_back(player1->hoveredLeftButton);
        buttons.push_back(player1->hoveredRightButton);

        buttons.push_back(player2->leftButton);
        buttons.push_back(player2->rightButton);
        buttons.push_back(player2->hoveredLeftButton);
        buttons.push_back(player2->hoveredRightButton);

        buttons.push_back(player3->leftButton);
        buttons.push_back(player3->rightButton);
        buttons.push_back(player3->hoveredLeftButton);
        buttons.push_back(player3->hoveredRightButton);

        buttons.push_back(player4->leftButton);
        buttons.push_back(player4->rightButton);
        buttons.push_back(player4->hoveredLeftButton);
        buttons.push_back(player4->hoveredRightButton);
//####################################################################################################

        //Loads text
        font = data->assetManager.GetFont("Berlin Sans FB");

        player1->chInfo.setPosition(370, 420);
        player2->chInfo.setPosition(1130, 420);
        player3->chInfo.setPosition(370, 940);
        player4->chInfo.setPosition(1130, 940);

        for(auto player : allPlayers){
            player->chInfo.setFont(font);
            player->Bunny.setFont(font);
            player->Cat.setFont(font);
            player->Dog.setFont(font);
            player->Pig.setFont(font);
        }

        player1->Bunny.setPosition(470, 450);
        player2->Bunny.setPosition(1230, 450);
        player3->Bunny.setPosition(470, 970);
        player4->Bunny.setPosition(1230, 970);
        player1->Cat.setPosition(475, 450);
        player2->Cat.setPosition(1235, 450);
        player3->Cat.setPosition(475, 970);
        player4->Cat.setPosition(1235, 970);
        player1->Dog.setPosition(490, 450);
        player2->Dog.setPosition(1250, 450);
        player3->Dog.setPosition(490, 970);
        player4->Dog.setPosition(1250, 970);
        player1->Pig.setPosition(480, 450);
        player2->Pig.setPosition(1240, 450);
        player3->Pig.setPosition(480, 970);
        player4->Pig.setPosition(1240, 970);


        for(auto player : allPlayers){
            player->charNames.push_back(player->Bunny);
            player->charNames.push_back(player->Cat);
            player->charNames.push_back(player->Dog);
            player->charNames.push_back(player->Pig);
        }

//####################################################################################################

        player1->opInfo.setFont(font);
        player1->opInfo.setString("Choose number of opponents: ");
        player1->opInfo.getString();
        player1->opInfo.setCharacterSize(30);
        player1->opInfo.setStyle(sf::Text::Bold);
        player1->opInfo.setPosition(370, 430);
        player1->opInfo.setColor(sf::Color::Transparent);

        player1->aiNumber0.setFont(font);
        player1->aiNumber0.setString("0");
        player1->aiNumber0.getString();
        player1->aiNumber0.setCharacterSize(60);
        player1->aiNumber0.setStyle(sf::Text::Bold);
        player1->aiNumber0.setPosition(560, 460);
        player1->aiNumber0.setColor(sf::Color::Transparent);

        player1->aiNumber1.setFont(font);
        player1->aiNumber1.setString("1");
        player1->aiNumber1.getString();
        player1->aiNumber1.setCharacterSize(60);
        player1->aiNumber1.setStyle(sf::Text::Bold);
        player1->aiNumber1.setPosition(560, 460);
        player1->aiNumber1.setColor(sf::Color::Transparent);

        player1->aiNumber2.setFont(font);
        player1->aiNumber2.setString("2");
        player1->aiNumber2.getString();
        player1->aiNumber2.setCharacterSize(60);
        player1->aiNumber2.setStyle(sf::Text::Bold);
        player1->aiNumber2.setPosition(560, 460);
        player1->aiNumber2.setColor(sf::Color::Transparent);

        player1->aiNumber3.setFont(font);
        player1->aiNumber3.setString("3");
        player1->aiNumber3.getString();
        player1->aiNumber3.setCharacterSize(60);
        player1->aiNumber3.setStyle(sf::Text::Bold);
        player1->aiNumber3.setPosition(560, 460);
        player1->aiNumber3.setColor(sf::Color::Transparent);

        player1->AINumbers.push_back(player1->aiNumber0);
        player1->AINumbers.push_back(player1->aiNumber1);
        player1->AINumbers.push_back(player1->aiNumber2);
        player1->AINumbers.push_back(player1->aiNumber3);

//####################################################################################################

        //Loads overlay that say if you are ready to play or join

        player2->ready.setTexture(this->data->assetManager.GetTexture("Ready"));
        player2->ready.setPosition(976,36);
        player2->ready.setColor(sf::Color::Transparent);

        player3->ready.setTexture(this->data->assetManager.GetTexture("Ready"));
        player3->ready.setPosition(208,552);
        player3->ready.setColor(sf::Color::Transparent);

        player4->ready.setTexture(this->data->assetManager.GetTexture("Ready"));
        player4->ready.setPosition(976,552);
        player4->ready.setColor(sf::Color::Transparent);

        player1->pressToPlay.setTexture(this->data->assetManager.GetTexture("Press to play"));
        player1->pressToPlay.setPosition(208,36);
        player1->pressToPlay.setColor(sf::Color::Transparent);

        player2->join.setTexture(this->data->assetManager.GetTexture("Join"));
        player2->join.setPosition(976,36);
        player2->join.setColor(sf::Color::White);

        player3->join.setTexture(this->data->assetManager.GetTexture("Join"));
        player3->join.setPosition(208,552);
        player3->join.setColor(sf::Color::White);

        player4->join.setTexture(this->data->assetManager.GetTexture("Join"));
        player4->join.setPosition(976,552);
        player4->join.setColor(sf::Color::White);


    }

    void CharSelectState::HandleInput() {
        sf::Event event;

        while(data->window.pollEvent(event)) {

            //PLAYER 1
            //Handles the mouse for player 1
            if (event.type == sf::Event::MouseMoved) mouseMoved = true;

            if (event.type == sf::Event::MouseButtonPressed) {
                //Left button click

                if (data->inputManager.IsSpriteClicked(player1->charSelect[0], sf::Mouse::Button::Left, data->window)) {
                    player1->LeftControl(GetPlayersConnected(), takenChar);
                }
                //Right button click
                if (data->inputManager.IsSpriteClicked(player1->charSelect[1], sf::Mouse::Button::Left, data->window)) {
                    player1->RightControl(GetPlayersConnected(), takenChar);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                player1->IsHoveredfalse();
                player2->IsHoveredfalse();
                player3->IsHoveredfalse();
                player4->IsHoveredfalse();
            }

            //Player 1 keyboard controls
            if (event.type == sf::Event::KeyPressed) {

                // Player 1 - ENTER button
                if(event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return) {
                    player1->Player1Enter(takenChar);
                    CheckOtherCharactersSelected(takenChar);
                    if(player1->enterCount == 3) {
                        if (player2->enterCount == 1 || player3->enterCount == 1 || player4->enterCount == 1) { // if the other players are not ready, player1 cant start the game
                            player1->enterCount = 2;
                        }
                        else GoToLevelState();
                    }
                }
                //Player 1 ESCAPE button
                if(event.key.code == sf::Keyboard::Escape) {
                    player1->Player1Back(takenChar);
                    if (player1->enterCount < 0) {
                        data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                    }
                }
                //Choose a character and number of AI's with the LEFT button
                if (event.key.code == sf::Keyboard::Left) {
                    player1->LeftControl(GetPlayersConnected(), takenChar);
                }

                //Choose a character and number of AI's with the RIGHT button
                if (event.key.code == sf::Keyboard::Right) {
                    player1->RightControl(GetPlayersConnected(), takenChar);
                }

            }

            if (event.type == sf::Event::KeyReleased) {
                player1->IsHoveredfalse();
                player2->IsHoveredfalse();
                player3->IsHoveredfalse();
                player4->IsHoveredfalse();
            }


            if(JOYSTICK2_A){
                if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[1] > minTimeJoystick) {
                    if ((player2->controlID == -1 || player2->controlID == 1) && player3->controlID != 1 &&
                        player4->controlID != 1) {
                        player2->controlID = 1;
                        player2->PlayersEnter(takenChar);
                        CheckOtherCharactersSelected(takenChar);

                        CheckAISelected();
                    } else if ((player3->controlID == -1 || player3->controlID == 1) && player2->controlID != 1 &&
                               player4->controlID != 1) {
                        player3->controlID = 1;
                        player3->PlayersEnter(takenChar);
                        CheckOtherCharactersSelected(takenChar);

                        CheckAISelected();
                    } else if ((player4->controlID == -1 || player4->controlID == 1) && player3->controlID != 1 &&
                               player2->controlID != 1) {
                        player4->controlID = 1;
                        player4->PlayersEnter(takenChar);
                        CheckOtherCharactersSelected(takenChar);

                        CheckAISelected();
                    }
                    lastTimePressed[1] = clockJoystick.getElapsedTime().asMilliseconds();
                }
            }
            if(JOYSTICK3_A){
                if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[2] > minTimeJoystick) {
                    if ((player2->controlID == -1 || player2->controlID == 2) && player3->controlID != 2 &&
                        player4->controlID != 2) {
                        player2->controlID = 2;
                        player2->PlayersEnter(takenChar);
                        CheckOtherCharactersSelected(takenChar);

                        CheckAISelected();
                    } else if ((player3->controlID == -1 || player3->controlID == 2) && player2->controlID != 2 &&
                               player4->controlID != 2) {
                        player3->controlID = 2;
                        player3->PlayersEnter(takenChar);
                        CheckOtherCharactersSelected(takenChar);

                        CheckAISelected();
                    } else if ((player4->controlID == -1 || player4->controlID == 2) && player2->controlID != 2 &&
                               player3->controlID != 2) {
                        player4->controlID = 2;
                        player4->PlayersEnter(takenChar);
                        CheckOtherCharactersSelected(takenChar);

                        CheckAISelected();
                    }
                    lastTimePressed[2] = clockJoystick.getElapsedTime().asMilliseconds();
                }
            }
            if(JOYSTICK4_A){
                if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[3] > minTimeJoystick) {
                    if ((player2->controlID == -1 || player2->controlID == 3) && player3->controlID != 3 &&
                        player4->controlID != 3) {
                        player2->controlID = 3;
                        player2->PlayersEnter(takenChar);
                        CheckOtherCharactersSelected(takenChar);

                        CheckAISelected();
                    } else if ((player3->controlID == -1 || player3->controlID == 3) && player2->controlID != 3 &&
                               player4->controlID != 3) {
                        player3->controlID = 3;
                        player3->PlayersEnter(takenChar);
                        CheckOtherCharactersSelected(takenChar);

                        CheckAISelected();
                    } else if ((player4->controlID == -1 || player4->controlID == 3) && player2->controlID != 3 &&
                               player3->controlID != 3) {
                        player4->controlID = 3;
                        player4->PlayersEnter(takenChar);
                        CheckOtherCharactersSelected(takenChar);

                        CheckAISelected();
                    }
                    lastTimePressed[3] = clockJoystick.getElapsedTime().asMilliseconds();
                }
            }


            //Player 1 Joystick controls
            if (event.type == sf::Event::JoystickMoved) {
                if (JOYSTICK_RIGHT){
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[0] > minTimeJoystick) {
                        player1->RightControl(GetPlayersConnected(), takenChar);
                        lastTimePressed[0] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }

                if (JOYSTICK_LEFT){
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[0] > minTimeJoystick) {
                        player1->LeftControl(GetPlayersConnected(), takenChar);
                        lastTimePressed[0] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }

                if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > -99 && sf::Joystick::getAxisPosition(0, sf::Joystick::X)< 99){
                    player1->IsHoveredfalse();
                    player2->IsHoveredfalse();
                    player3->IsHoveredfalse();
                    player4->IsHoveredfalse();
                }
            }

            //Press X to choose characters and add AI
            if(JOYSTICK1_A){
                if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[0] > minTimeJoystick) {
                    player1->Player1Enter(takenChar);
                    if (player1->enterCount == 3) {
                        GoToLevelState();
                    }
                    lastTimePressed[0] = clockJoystick.getElapsedTime().asMilliseconds();
                }
            }

            //Press B to go back
            if(JOYSTICK1_B){
                if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[0] > minTimeJoystick) {
                    player1->Player1Back(takenChar);
                    if (player1->enterCount < 0) {
                        data->stateMachine.AddState(StateRef(new MenuState(this->data)));
                    }
                    lastTimePressed[0] = clockJoystick.getElapsedTime().asMilliseconds();
                }
            }

            //PLAYER 2
            // Player 2 - A and D to choose character
            // Q as enter to join, choose a character and get ready to play
            // E as ESCAPE from be ready to play, to select character, to not join game
            if(player2->controlID!=-1) {
                if (sf::Joystick::isButtonPressed(player2->controlID, 2)) {
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[1] > minTimeJoystick) {
                        player2->PlayersBack(takenChar);
                        lastTimePressed[1] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }

                //A to choose left between characters
                if (sf::Joystick::getAxisPosition(player2->controlID, sf::Joystick::X) == -100) {
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[1] > minTimeJoystick) {
                        player2->SecondLeftControl(takenChar);
                        lastTimePressed[1] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }

                //D to choose right between characters
                if (sf::Joystick::getAxisPosition(player2->controlID, sf::Joystick::X) == 100) {
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[1] > minTimeJoystick) {
                        player2->SecondRightControl(takenChar);
                        lastTimePressed[1] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }
            }

            //PLAYER 3
            // Player 3 - J and L to select arrow, press U to select character.
            //U for ENTER to choose character
            //O for ESCAPE to go back
            if(player3->controlID!=-1) {
                if (sf::Joystick::isButtonPressed(player3->controlID, 2)) {
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[2] > minTimeJoystick) {
                        player3->PlayersBack(takenChar);
                        lastTimePressed[2] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }

                //J to scroll left between characters
                if (sf::Joystick::getAxisPosition(player3->controlID, sf::Joystick::X) == -100) {
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[2] > minTimeJoystick) {
                        player3->SecondLeftControl(takenChar);
                        lastTimePressed[2] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }

                //L to scroll right between characters
                if (sf::Joystick::getAxisPosition(player3->controlID, sf::Joystick::X) == 100) {
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[2] > minTimeJoystick) {
                        player3->SecondRightControl(takenChar);
                        lastTimePressed[2] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }
            }

            //PLAYER 4
            // Player 4 - Select character with num-buttons
            //NUM 7 for ENTER to choose character
            //NUM 9 for ESCAPE to go back
            if(player4->controlID!=-1) {
                if (sf::Joystick::isButtonPressed(player4->controlID, 2)) {
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[3] > minTimeJoystick) {
                        player4->PlayersBack(takenChar);
                        lastTimePressed[3] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }

                //NUM4 to scroll left between characters
                if (sf::Joystick::getAxisPosition(player4->controlID, sf::Joystick::X) == -100) {
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[3] > minTimeJoystick) {
                        player4->SecondLeftControl(takenChar);
                        lastTimePressed[3] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }
                //NUM 6 to scroll right between characters
                if (sf::Joystick::getAxisPosition(player4->controlID, sf::Joystick::X) == 100) {
                    if(clockJoystick.getElapsedTime().asMilliseconds() - lastTimePressed[3] > minTimeJoystick) {
                        player4->SecondRightControl(takenChar);
                        lastTimePressed[3] = clockJoystick.getElapsedTime().asMilliseconds();
                    }
                }
            }
        }

        //Sets every movement to false;
        mouseMoved = false;
    }

    void CharSelectState::Update(float delta) {}

    void CharSelectState::Draw(float delta) {

        //Draw background
        data->window.clear();
        data->window.draw(charBackground);

        for(auto player : allPlayers){
            //Draw text
            data->window.draw(player->chInfo);
            data->window.draw(player->charNames[player->nameChoice]);

            //Draw charachters
            data->window.draw(player->characters[player->charChoice]);

        }
        data->window.draw(player1->opInfo);
        data->window.draw(player1->AINumbers[player1->AIChoice]);

        //Draw join screen
        data->window.draw(player2->join);
        data->window.draw(player3->join);
        data->window.draw(player4->join);

        //Draw ready screen
        data->window.draw(player2->ready);
        data->window.draw(player3->ready);
        data->window.draw(player4->ready);

        //Draw press to play screen
        data->window.draw(player1->pressToPlay);

        //Draws buttons
        IsHovered();

        //Displays everything
        data->window.display();
    }

    int CharSelectState::GetPlayersConnected() {
        int charselected = 0;
        for(int i = 1; i<allPlayers.size(); i++){
            if(allPlayers[i]->isCharConnected){
                charselected++;
            }
        }
        return charselected;
    }

    void CharSelectState::GoToLevelState() {

        player1->isReady=true;

        for(auto player : allPlayers){
            data->chosenSprite[player->id] = (int)player->charChoice;
            data->playerInfo[player->id] = player;
        }
        data->numbersOfAI = (int) player1->AIChoice;
        if(player2->isReady || player3->isReady || player4->isReady) singlePlayer = false;
        data->stateMachine.AddState(StateRef(new LevelSelectState(this->data, this->singlePlayer)),false);

    }


    players::players() {

        bunny.setScale(0.35,0.35);
        cat.setScale(0.35,0.35);
        dog.setScale(0.35,0.35);
        pig.setScale(0.35,0.35);

        leftButton.setScale(0.35,0.35);
        rightButton.setScale(0.35,0.35);
        hoveredLeftButton.setScale(0.35,0.35);
        hoveredRightButton.setScale(0.35,0.35);

        chInfo.setString("Choose your character: ");
        chInfo.getString();
        chInfo.setCharacterSize(38);
        chInfo.setStyle(sf::Text::Bold);

        Bunny.setString("Snusken");
        Bunny.getString();
        Bunny.setCharacterSize(60);
        Bunny.setStyle(sf::Text::Bold);

        Cat.setString("Dasken");
        Cat.getString();
        Cat.setCharacterSize(60);
        Cat.setStyle(sf::Text::Bold);

        Dog.setString("Tassen");
        Dog.getString();
        Dog.setCharacterSize(60);
        Dog.setStyle(sf::Text::Bold);

        Pig.setString("Slasken");
        Pig.getString();
        Pig.setCharacterSize(60);
        Pig.setStyle(sf::Text::Bold);

        controlID=-1;

        //Sets the time you push ENTER button on each character to 0
        enterCount = 0;
    }

    void players::RightControl(int playersConnected, std::map<int, bool> &takenChar) {
        isHoveredRight = true;
        if(enterCount == 0) {
                do {
                    if (charChoice == characters.size() - 1) {
                        charChoice = 0;
                        nameChoice = 0;
                    } else {
                        charChoice++;
                        nameChoice++;
                    }
                } while (takenChar[charChoice]);

        }


        if (isCharConnected && !isAISelected) {
            if (AIChoice == AINumbers.size() - 1 - playersConnected) {
                AIChoice = 0;
            } else AIChoice++;
        }

    }

    void players::LeftControl(int playersConnected, std::map<int, bool> &takenChar) {
        isHoveredLeft = true;
        if(enterCount == 0) {
                do {
                    if (charChoice == 0) {
                        charChoice = characters.size() - 1;
                        nameChoice = characters.size() - 1;
                    } else {
                        charChoice--;
                        nameChoice--;
                    }
                } while (takenChar[charChoice]);
        }
        if(isCharConnected && !isAISelected) {
            if (AIChoice == 0) {
                AIChoice = AINumbers.size() - 1 - playersConnected;
            } else AIChoice--;
        }
    }

    void players::SecondLeftControl(std::map<int, bool> &takenChar) {
        isHoveredLeft = true;
        if(enterCount == 1) {
            do {
                if (charChoice == 0) {
                    charChoice = characters.size() - 1;
                    nameChoice = characters.size() - 1;
                } else {
                    charChoice--;
                    nameChoice--;
                }
            }   while(takenChar[charChoice]);
        }
    }

    void players::SecondRightControl(std::map<int, bool> &takenChar) {
        isHoveredRight = true;
        if(enterCount==1) {
                do{
                    if (charChoice == characters.size() - 1) {
                        charChoice = 0;
                        nameChoice = 0;
                    }
                    else{
                        charChoice++;
                        nameChoice++;
                    }
                }    while(takenChar[charChoice]);
        }
    }

    void players::Player1Enter(std::map<int, bool> &takenChar) {
        enterCount++;

        //If player has chosen a character, they get to choose how many AI to play against
        if (enterCount == 1) {
            isCharConnected = true;
            isAISelected = false;
            opInfo.setColor(sf::Color::White);
            chInfo.setColor(sf::Color::Transparent);

            charNames[0].setColor(sf::Color::Transparent);
            charNames[1].setColor(sf::Color::Transparent);
            charNames[2].setColor(sf::Color::Transparent);
            charNames[3].setColor(sf::Color::Transparent);

            AINumbers[0].setColor(sf::Color::White);
            AINumbers[1].setColor(sf::Color::White);
            AINumbers[2].setColor(sf::Color::White);
            AINumbers[3].setColor(sf::Color::White);
        }

        //Character and AI chosen; Press to play!
        if (enterCount == 2) {
            isAISelected = true;
            left = false;
            right = false;
            pressToPlay.setColor(sf::Color::White);
            takenChar[charChoice] = true;
            isReady = true;
        }

    }

    void players::PlayersEnter(std::map<int, bool> &takenChar) {
        enterCount ++;

        if(enterCount == 1){
            join.setColor(sf::Color::Transparent);
            isCharConnected = true;
        }

        if(enterCount == 2) {
            takenChar[charChoice] = true;
            isReady = true;
            ready.setColor(sf::Color::White);
        }

        if(enterCount > 2){
            enterCount = 2;
        }
    }

    void players::Player1Back(std::map<int, bool> &takenChar) {
        enterCount--;
        takenChar[charChoice] = false;

        //Takes player back to choosing a character
        if (enterCount == 0) {
            opInfo.setColor(sf::Color::Transparent);
            chInfo.setColor(sf::Color::White);

            charNames[0].setColor(sf::Color::White);
            charNames[1].setColor(sf::Color::White);
            charNames[2].setColor(sf::Color::White);
            charNames[3].setColor(sf::Color::White);

            AINumbers[0].setColor(sf::Color::Transparent);
            AINumbers[1].setColor(sf::Color::Transparent);
            AINumbers[2].setColor(sf::Color::Transparent);
            AINumbers[3].setColor(sf::Color::Transparent);
        }
        //Takes the player back to choosing the number of AI's
        if (enterCount == 1) {
            isAISelected = false;
            isReady = false;
            opInfo.setColor(sf::Color::White);
            chInfo.setColor(sf::Color::Transparent);

            charNames[0].setColor(sf::Color::Transparent);
            charNames[1].setColor(sf::Color::Transparent);

            AINumbers[0].setColor(sf::Color::White);
            AINumbers[1].setColor(sf::Color::White);
            AINumbers[2].setColor(sf::Color::White);

            pressToPlay.setColor(sf::Color::Transparent);
        }
    }

    void players::PlayersBack(std::map<int, bool> &takenChar) {
        enterCount --;
        takenChar[charChoice] = false;

        if(enterCount < 0){
            enterCount = 0;
        }

        if(enterCount == 0){
            join.setColor(sf::Color::White);
            isCharConnected = false;
            left = false;
            right = false;
        }

        if(enterCount == 1) {
            ready.setColor(sf::Color::Transparent);
        }
    }

    void players::IsHoveredfalse() {
        isHoveredLeft = false;
        isHoveredRight = false;

    }

    void CharSelectState::IsHovered() {
        //Draw buttons
        if(!player1->isHoveredLeft) {
            data->window.draw(buttons[buttonChoice = 0]);
        } else data->window.draw(buttons[buttonChoice = 2]);

        if(!player1->isHoveredRight) {
            data->window.draw(buttons[buttonChoice = 1]);
        } else data->window.draw(buttons[buttonChoice = 3]);

        if(!player2->isHoveredLeft) {
            data->window.draw(buttons[buttonChoice = 4]);
        } else data->window.draw(buttons[buttonChoice = 6]);

        if(!player2->isHoveredRight) {
            data->window.draw(buttons[buttonChoice = 5]);
        } else data->window.draw(buttons[buttonChoice = 7]);

        if(!player3->isHoveredLeft) {
            data->window.draw(buttons[buttonChoice = 8]);
        } else data->window.draw(buttons[buttonChoice = 10]);

        if(!player3->isHoveredRight) {
            data->window.draw(buttons[buttonChoice = 9]);
        } else data->window.draw(buttons[buttonChoice = 11]);

        if(!player4->isHoveredLeft) {
            data->window.draw(buttons[buttonChoice = 12]);
        } else data->window.draw(buttons[buttonChoice = 14]);

        if(!player4->isHoveredRight) {
            data->window.draw(buttons[buttonChoice = 13]);
        } else data->window.draw(buttons[buttonChoice = 15]);
    }

    void CharSelectState::CheckAISelected() {
        if(4-GetPlayersConnected() == player1->AIChoice){
            player1->AIChoice--;
        }
    }

    void CharSelectState::CheckOtherCharactersSelected(std::map<int, bool> &takenChar) {
        for(auto player : allPlayers){
            if(player->enterCount == 2) {
                for (auto otherPlayers : allPlayers) {
                    if (otherPlayers == player) continue;

                    if (takenChar[otherPlayers->charChoice]) {
                        if (otherPlayers->enterCount<2) {
                            do {
                                if (otherPlayers->charChoice == otherPlayers->characters.size() - 1) {
                                    otherPlayers->charChoice = 0;
                                    otherPlayers->nameChoice = 0;
                                } else {
                                    otherPlayers->charChoice++;
                                    otherPlayers->nameChoice++;
                                }
                            } while (takenChar[otherPlayers->charChoice]);
                        }
                    }
                }
            }
        }
    }
}