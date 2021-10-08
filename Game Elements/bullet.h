#ifndef KJELEDYR_BULLET_H
#define KJELEDYR_BULLET_H

#include <SFML/Graphics/Sprite.hpp>
#include <Game Engine/game.h>

namespace Kjeledyr{

    class Bullet {

    public:
        Bullet(int playerX, int playerY, bool directionLeft, GameDataRef &data); // Spawns a bullet from the players x and y position and the direction facing
        sf::Sprite GetSprite();
        void Move();
        bool IsWithingWindow(); // Checks if the bullet is within the window


    protected:
        int x;
        int y;
        int xSpeed;
        sf::Sprite sprite;
        sf::Texture *texture;

    };

}

#endif //KJELEDYR_BULLET_H
