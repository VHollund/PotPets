#ifndef KJELEDYR_POWERUP_H
#define KJELEDYR_POWERUP_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Game Engine/game.h>


namespace Kjeledyr {

    enum class PowerType { gun, invincible, melee };

    class powerUp {

    public:
        powerUp(PowerType type, GameDataRef &data);
        PowerType GetType();
        void SetX(int x);
        void SetY(int y);
        int GetX();
        int GetY();
        void SetSprite();
        sf::Sprite GetSprite();
        sf::Sprite DrawSprite();
        void SetRandomSpawn(std::vector<std::pair<int, int>> &powerUpSpawns);
        int GetRandomNumber(int min, int max); //returns a random nubmer between min and max

        int allPowerUpsCount = 3; // int which says how many diffrent powerups there are in total. Important to change if we add/delete powerups.
    protected:
        int x;
        int y;
        int size;
        sf::Sprite sprite; //rectangleshape byttes til sf::Sprite
        sf::Texture *texture;
        PowerType type;
    };
}

#endif //KJELEDYR_POWERUP_H
