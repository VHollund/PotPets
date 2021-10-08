#ifndef KJELEDYR_AMMO_H
#define KJELEDYR_AMMO_H

#include <list>
#include <SFML/Graphics/RectangleShape.hpp>

namespace Kjeledyr {

    struct ammoRect {
        int x;
        int y;
        sf::RectangleShape rect;
    };

    class Ammo {
    public:
        Ammo(int playerX, int playerY);
        std::list<ammoRect*> GetTotalAmmo();
        void SetRects(int playerX, int playerY); //Sets the ammo rectangles on the player which displayes ammo left.
        void UseAmmo();
        bool OutOfAmmo();

    protected:
        int rectWidth = 10;
        int rectHeight = 5;
        const int magazineSize = 5;
        int ammoLeft;
        std::list<ammoRect*> totalAmmo;

    };
}

#endif //KJELEDYR_AMMO_H
