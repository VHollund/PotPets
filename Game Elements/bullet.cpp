#include <DEFINITIONS.h>
#include "bullet.h"

namespace Kjeledyr{

    Bullet::Bullet(int playerX, int playerY, bool directionLeft, GameDataRef &data) {
        this->x = playerX+32;
        this->y = playerY+20;
        if (directionLeft) {
            xSpeed = 10;
        } else xSpeed = -10;

        data->assetManager.LoadTexture("PowerUps", POWERUPS_FILEPATH);
        sprite.setTexture(data->assetManager.GetTexture("PowerUps"));

        if(!directionLeft){
            sprite.setTextureRect(sf::IntRect(TILE_SIZE*4, 0, -TILE_SIZE, TILE_SIZE));
        }
        else sprite.setTextureRect(sf::IntRect(TILE_SIZE*3, 0, TILE_SIZE, TILE_SIZE));
        sprite.setPosition(x,y);
    }

    sf::Sprite Bullet::GetSprite() {
        return sprite;
    }

    void Bullet::Move() {
        x += xSpeed;
        sprite.setPosition(x,y);
    }

    bool Bullet::IsWithingWindow() {
        return !(x<-TILE_SIZE || 1920+TILE_SIZE<x);
    }
}