#include <iostream>
#include <plog/Log.h>
#include "player.h"

namespace Kjeledyr {
    Player::Player(int ChosenSprite, std::vector<std::pair<int, int>> &spawnPoints) {
        this->x =  -200*(id+1);
        this->y =  -200*(id+1);

        playerState = PlayerStates::normal;


        this->AI= false;
        spriteOffSet = ChosenSprite;

    }

    int Player::GetControllerID() {return controllerID;}
    void Player::SetControllerID(int ID) {this->controllerID=ID;}

    void Player::SetSpriteID(int ID){
            this->spriteOffSet = ID;

    }

    void Player::HandleInput(std::map<int,PlayerObject*> allPlayers, GameDataRef &data) {
        if (sf::Joystick::getAxisPosition(controllerID, sf::Joystick::X) >= 30) {
            if (GetX() < SCREEN_WIDTH - PLAYER_WIDTH) {
                SetXSpeed(PLAYER_XSPEED);
            } else if (GetX() >= SCREEN_WIDTH - PLAYER_WIDTH) SetXSpeed(0);
        }

        if (sf::Joystick::getAxisPosition(controllerID, sf::Joystick::X) <= -30) {
            if (GetX() > 10) {
                SetXSpeed(-PLAYER_XSPEED);
            } else if (GetX() <= 10) SetXSpeed(0);
        }

        if(sf::Joystick::getAxisPosition(controllerID,sf::Joystick::X)<=29&&
           sf::Joystick::getAxisPosition(controllerID,sf::Joystick::X)>=-29)
            SetXSpeed(0);

        if (sf::Joystick::isButtonPressed(controllerID, 0)) {
            Jump();
        }

        if (sf::Joystick::isButtonPressed(controllerID, 2)) {
            CheckAttack(allPlayers, data);
        }
    }
}
