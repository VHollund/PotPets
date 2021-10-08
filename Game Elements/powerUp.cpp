#include <DEFINITIONS.h>
#include <chrono>
#include <SFML/Graphics/Texture.hpp>
#include <random>
#include <iostream>
#include <Game Engine/game.h>
#include "powerUp.h"

namespace Kjeledyr {

    powerUp::powerUp(PowerType type, GameDataRef &data) {

        this->type = type;
        SetX(400);
        SetY(400);
        size = 64;

        sprite.setTexture(data->assetManager.GetTexture("PowerUps"));

        if(this->type==PowerType::gun){ sprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE)); }
        else if(this->type==PowerType::invincible){ sprite.setTextureRect(sf::IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE)); }
        else if(this->type==PowerType::melee){ sprite.setTextureRect(sf::IntRect(TILE_SIZE*2, 0, TILE_SIZE, TILE_SIZE)); }
        else  sprite.setTextureRect(sf::IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE));


    }

    void powerUp::SetX(int x) { this->x = x; }
    void powerUp::SetY(int y) { this->y = y; }
    int powerUp::GetX() { return x; }
    int powerUp::GetY() { return y; }

    void powerUp::SetSprite() {
        sprite.setPosition(x,y);
    }

    sf::Sprite powerUp::DrawSprite() {
        SetSprite();
        return sprite;
    }

    void powerUp::SetRandomSpawn(std::vector<std::pair<int, int>> &powerUpSpawns) {
        int randomPos = GetRandomNumber(0, (int)powerUpSpawns.size() -1);
        y = powerUpSpawns[randomPos].first*TILE_SIZE;
        x = powerUpSpawns[randomPos].second*TILE_SIZE;
    }

    int powerUp::GetRandomNumber(int min, int max){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }

    sf::Sprite powerUp::GetSprite() {
        return sprite;
    }

    PowerType powerUp::GetType() {
        return type;
    }
}