#ifndef KJELEDYR_BACKGROUNDANIMATIONS_H
#define KJELEDYR_BACKGROUNDANIMATIONS_H
#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

namespace Kjeledyr{

    enum allTypes {bird, smallcloud, bigcloud, };

    struct bObject{
        allTypes type;
        int x;
        int y;
        int xSpeed;
        sf::Sprite sprite;

        void SetSprite(int x, int y);
        sf::Sprite DrawSprite();

        int GetX();
        int GetY();
        void SetX(int x);
        void SetY(int y);
        void SetXSpeed(int xspeed);

        int randomnr;
        void NewPosition(); //Gives the object a new random position, sprite and speed etc
        void CheckAnimation(); // Checks if the animation is going to play flipped or not(left/right)
        void PlayAnimation(); // Plays the animation

        sf::Clock clock;
        int frameDuration;
        int frame;
        int frameCount;
        int flipped;
        int flipped2;
        int ytile;
        int level;
    };

    class backgroundAnimations {
    public:
        backgroundAnimations(int levelSelected);
        void tick();
        bObject GetObject(int index);
        int GetAllObjectsSize();

    private:
        std::vector<bObject*> allObjects; // All objects in a vector
        int totalObjects = 0; // Set how many object that should be on the screen at the same time -> Gets set in the constructor
        unsigned seed;
        int level; // Stores which level is chosen
    };
}
#endif //KJELEDYR_BACKGROUNDANIMATIONS_H
