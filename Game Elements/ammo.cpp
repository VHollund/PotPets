#include "ammo.h"

namespace Kjeledyr {

    Ammo::Ammo(int playerX, int playerY) {

        ammoLeft = magazineSize;

        for (int i = 0; i < magazineSize; ++i) {
            auto rect = new ammoRect();

            rect->x = playerX;
            rect->y = playerY + (i * 6);

            rect->rect.setSize(sf::Vector2f(rectWidth, rectHeight));
            rect->rect.setPosition(sf::Vector2f(rect->x, rect->y));

            rect->rect.setFillColor(sf::Color::Red);
            rect->rect.setOutlineColor(sf::Color::Black);
            rect->rect.setOutlineThickness(1);
            totalAmmo.emplace_back(rect);

        }
    }

    std::list<ammoRect *> Ammo::GetTotalAmmo() {
        return totalAmmo;
    }

    void Ammo::SetRects(int playerX, int playerY) {
        int i = 0;
        for(auto rect : totalAmmo){
            rect->x = playerX;
            rect->y = playerY + (i * 6);
            rect->rect.setPosition(rect->x, rect->y);
            i++;
        }
    }

    void Ammo::UseAmmo() {
        ammoLeft--;
        totalAmmo.pop_front();

    }

    bool Ammo::OutOfAmmo() { return ammoLeft<=0; }
}
