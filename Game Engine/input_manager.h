#ifndef KJELEDYR_INPUT_MANAGER_H
#define KJELEDYR_INPUT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>

// Handles inputs and game logic

namespace Kjeledyr {

    class InputManager {
    public:
        InputManager(){}
        ~InputManager(){}

        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
        bool IsSpriteHovered(sf::Sprite object, sf::RenderWindow &window);

        int GetCurrentSprite(std::map<int, sf::Sprite> &buttons,
                             int &currentSprite,
                             bool mouseMoved,
                             bool up,
                             bool down,
                             sf::RenderWindow &window);



    protected:

    };
}

#endif
