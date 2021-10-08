#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <DEFINITIONS.h>
#include <random>
#include <chrono>
#include "backgroundAnimations.h"

namespace Kjeledyr{

    backgroundAnimations::backgroundAnimations(int levelSelected) {
        auto *tileset = new sf::Texture();
        if (!tileset->loadFromFile("Resources/res/backgroundobjects.png")) {
            std::cout << "FAILED TO LOAD BACKGROUND SHEET. (class backgroundAnimations.cpp)";
        }

        level = levelSelected;

        if(level==0 || level==2){
            totalObjects = 5;
        }
        if(level==1){
            totalObjects = 3;
        }


        for (int i = 0; i < totalObjects; ++i) {
            auto *temp = new bObject();
            temp->sprite.setTexture(*tileset);
            temp->randomnr = i;
            temp->level = level;
            temp->NewPosition();
            allObjects.emplace_back(temp);
        }

    }

    void backgroundAnimations::tick() {
        for(auto object : allObjects){
           object->SetX(object->GetX()+object->xSpeed);
            if(object->type == bird ){
                object->PlayAnimation();
            }
            if(object->GetX() > 2000 && object->xSpeed > 0){
                object->NewPosition();
            }
            if(object->GetX() < -TILE_SIZE*2 && object->xSpeed < 0){
                object->NewPosition();
            }
        }
    }

    bObject backgroundAnimations::GetObject(int index) {
        return *allObjects[index];
    }

    int backgroundAnimations::GetAllObjectsSize() {
        return (int) allObjects.size();
    }

    void bObject::SetSprite(int x, int y) {
        this->x = x;
        this->y = y;
        sprite.setPosition(x, y);
    }

    sf::Sprite bObject::DrawSprite() {
        SetSprite(GetX(), GetY());
        return sprite;
    }

    int bObject::GetX() {
        return this->x;
    }

    int bObject::GetY() {
        return this->y;
    }

    void bObject::SetX(int x) {
        this->x = x;
    }

    void bObject::SetY(int y) {
        this->y = y;
    }

    void bObject::NewPosition() {

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count()+randomnr;
        std::default_random_engine generator(seed);

        std::uniform_int_distribution<int> distribution(1,10);
        int rCordinate = distribution(generator);

        std::uniform_int_distribution<int> distribution2(0,1);
        int rDirection = distribution2(generator);

        std::uniform_int_distribution<int> distribution3(1,2);
        int rSpeed = distribution3(generator);

        std::uniform_int_distribution<int> distribution4(0,2);
        int rSprite = distribution4(generator);
        if(level == 1){ rSprite = 0;}
        if(rSprite==0) {
            if(level == 0) {
                sprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
                frameCount = 14;
            }
            else if(level == 1){
                sprite.setTextureRect(sf::IntRect(0, TILE_SIZE*1, TILE_SIZE, TILE_SIZE));
                frameCount = 3;
            }
            else if(level == 2){
                sprite.setTextureRect(sf::IntRect(0, TILE_SIZE*2, TILE_SIZE, TILE_SIZE));
                frameCount = 7;
            }

            type = bird;
            frame = 0;
        }
        else if(rSprite==1){
            sprite.setTextureRect(sf::IntRect(TILE_SIZE*6, TILE_SIZE*1, TILE_SIZE*2, TILE_SIZE));
            type = smallcloud;
        }
        else if(rSprite==2){
            sprite.setTextureRect(sf::IntRect(TILE_SIZE*6, TILE_SIZE*3, TILE_SIZE*2, TILE_SIZE));
            type = bigcloud;
        }

        if(rDirection == 0){
            distribution = std::uniform_int_distribution<int>(-300,-TILE_SIZE);
            rCordinate = distribution(generator);
            SetX(rCordinate);
            SetXSpeed(rSpeed);
        }
        else if(rDirection == 1) {
            distribution = std::uniform_int_distribution<int>(1920,2500);
            rCordinate = distribution(generator);
            SetX(rCordinate);
            SetXSpeed(-rSpeed);
        }
        distribution = std::uniform_int_distribution<int>(10,400);
        rCordinate = distribution(generator);
        SetY(rCordinate);

        if(type == bird){
            if(rSpeed==1){
                if(level==0 || level==2) {
                    frameDuration = 80;
                }
                if (level==1){
                    frameDuration = 80;
                }
            }
            if(rSpeed==2){
                if(level==0 || level==2) {
                    frameDuration = 50;
                }
                if (level==1){
                    frameDuration = 80;
                }
            }
            else {
                //LOGD << "Frameduration not set for this speed. Setting frameDuration = 80. (backgroundAnimations.cpp)";
                frameDuration = 80;
            }
        }
    }

    void bObject::SetXSpeed(int xspeed) {
        this->xSpeed = xspeed;
    }

    void bObject::PlayAnimation() {
        CheckAnimation();

        if (clock.getElapsedTime().asMilliseconds() < frameDuration)
            return;

        if (++frame >= frameCount)
            frame = 0;

        clock.restart();
        sprite.setTextureRect(sf::IntRect(frame*TILE_SIZE +flipped2, level*TILE_SIZE, flipped*TILE_SIZE, TILE_SIZE));
    }

    void bObject::CheckAnimation() {
        if (xSpeed>0){
            flipped = 1;
            flipped2 = 0;
        }
        if (xSpeed<0){
            flipped = -1;
            flipped2 = TILE_SIZE;
        }
    }
}
