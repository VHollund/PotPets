#include <cmath>
#include <iostream>
#include <plog/Log.h>
#include "AiPlayer.h"

namespace Kjeledyr {
    AiPlayer::AiPlayer(int ChosenSprite, std::vector<std::pair<int, int>> &spawnPoints) {
        auto *tileset = new sf::Texture();
        if (!tileset->loadFromFile("Resources/res/PlayerTileSet.png")) {
            LOGF<<"Failed to Load: PlayerTileSet.png";
        }

        sprite.setTexture(*tileset);
        sprite.setTextureRect(sf::IntRect(PLAYER_HEIGHT, 0, -PLAYER_WIDTH, PLAYER_HEIGHT));

        this->x =  -200*(id+1);
        this->y =  -200*(id+1);

        playerState = PlayerStates::normal;
        spriteOffSet = ChosenSprite;

        this->AI = true;
    }


    void AiPlayer::UpRight() { //Jump and move right
        if(!jumping){
            jumpingRight=true;
            Jump();
            xSpeed = PLAYER_XSPEED;
        }
        else if(collisionBot){jumping=false;}
    }


    void AiPlayer::UpLeft() { //Jump and move Left
        if(!jumping){
            jumpingLeft=true;
            Jump();
            xSpeed = -PLAYER_XSPEED;
        }
        else if(collisionBot){jumping=false;}
    }


    void AiPlayer::findTarget(std::map<int, PlayerObject*> players) { //itterates through all players to find closest one
        double LowestDistance = INT32_MAX;
        double distance;


        for (auto current:players) { //go through every player object, to locate the closest one using pythagoras
            if(current.second!=this) { //if current player is this(the Ai trying to find target), skip it
                distance = std::sqrt(((current.second->GetX() - this->x) ^ 2) + ((current.second->GetY() - this->y) ^ 2)); //setting distance to target
                if (distance < LowestDistance) { //if distance to target is lower then priveus lowest distance, new target is set.
                    LowestDistance = distance;
                    this->Xdirection = current.second->GetX();
                    this->Ydirection = current.second->GetY();
                    currentTar=current.second;
                }
            }
        }
    }


    void AiPlayer::moveDir(std::vector<AiRoutes*> routes, std::map<int,PlayerObject*> Allplayers) { //Ai's movement

        if(Ydirection != y) { //If target is not on same height, focus is set, and we use findRoutes.
            if (Xdirection < x && Ydirection > y) {
                focus = DOWN_LEFT;
            } else if (Xdirection > x && Ydirection > y) {
                focus = DOWN_RIGHT;
            } else if (Xdirection < x && Ydirection < y) {
                focus = UP_LEFT;
            } else if (Xdirection > x && Ydirection < y) {
                focus = UP_RIGHT;
            } else if (Xdirection == x && (Ydirection > y) || Ydirection < y) { //To avoid that AI locks itself un top of player and wont move we set a rand function in here
                focus = rand() % 4 + 57;
                SetTrapped(true);
            }

            this->last=currentTar;
            FindRoute(routes);
        }
        else if(y==Ydirection){ //If target is on same height level, move towards target
            focus=-1;
            if(Xdirection>x&& !jumping){
                if (GetX() < SCREEN_WIDTH - PLAYER_WIDTH) {
                    SetXSpeed(PLAYER_XSPEED);
                } else if (GetX() >= SCREEN_WIDTH - PLAYER_WIDTH) SetXSpeed(0);
            }
            if(Xdirection<x&&!jumping){
                if (GetX() > 10) {
                    SetXSpeed(-PLAYER_XSPEED);
                } else if (GetX() <= 10) SetXSpeed(0);
            }


            if (Xdirection >= x - PLAYER_WIDTH && !isFlipped && Xdirection<x+PLAYER_WIDTH){//sjekker om player er innenfor 1 rute avstand på begge sider
                MeleeAttack(Allplayers);
            }
            else if(Xdirection < x + PLAYER_WIDTH && isFlipped && Xdirection>=x){
                MeleeAttack(Allplayers);
            }
            this->last=currentTar;
        }
    }



    void AiPlayer::FindRoute(std::vector<AiRoutes*> routes) {
        int closeX=INT32_MAX;
        auto chosen=routes.begin();
        for(auto route=routes.begin();route!=routes.end();route++){ //iterate through all routes
            if(route.operator*()->GetY() >= y && route.operator*()->GetY()<=y+PLAYER_HEIGHT){ //check correct height level
                if(route.operator*()->GetDir()==focus){ //Check correct fucus direction
                    if(abs(route.operator*()->GetX()-x)<closeX){ //check distance to route, if its lower the current chosen, switch
                        closeX=abs(route.operator*()->GetX()-x);
                        chosen=route;
                    }

                }
            }
        }
        if(chosen.operator*()->GetX()>=x && chosen.operator*()->GetX()<=x+PLAYER_WIDTH && !jumping){
            UseRoute(chosen.operator*());
            SetTrapped(false); //if an AI can use a route, it is no longer trapped
        }//on triggerpoint
        else if(chosen.operator*()->GetX()>x && !jumping){
            if (GetX() < SCREEN_WIDTH - PLAYER_WIDTH) {
                SetXSpeed(PLAYER_XSPEED);
            } else if (GetX() >= SCREEN_WIDTH - PLAYER_WIDTH) SetXSpeed(0);
        } //move towards route point
        else if(chosen.operator*()->GetX()<x && !jumping){if (GetX() > 10) {
                SetXSpeed(-PLAYER_XSPEED);
            } else if (GetX() <= 10) SetXSpeed(0);
        }

        if(collisionRight && xSpeed>=0){UpRight();}
        if(collisionLeft && xSpeed <=0){UpLeft();}
    }



    void AiPlayer::UseRoute(AiRoutes* route) {
        //When on target route
        if (focus == UP_RIGHT) {
            UpRight();
        } else if (focus == UP_LEFT) {
            UpLeft();
        } else if(focus == DOWN_RIGHT){
            if (GetX() < SCREEN_WIDTH - PLAYER_WIDTH) {
                SetXSpeed(PLAYER_XSPEED);
            } else if (GetX() >= SCREEN_WIDTH - PLAYER_WIDTH) SetXSpeed(0);
        } else if(focus == DOWN_LEFT){
            if (GetX() > 10) {
                SetXSpeed(-PLAYER_XSPEED);
            } else if (GetX() <= 10) SetXSpeed(0);
        }
    }

    bool AiPlayer::CheckIfTrapped(){
        return this->trapped;
    }

    void AiPlayer::SetTrapped(bool trapped){
        this->trapped = trapped;
    }
}
