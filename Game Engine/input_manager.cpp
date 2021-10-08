#include <iostream>
#include <plog/Log.h>
#include "input_manager.h"

// Example of how this class works, needs to be changed to fit our game needs

namespace Kjeledyr{

    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window){

        if(sf::Mouse::isButtonPressed(button)){
            sf::IntRect tempRect(object.getPosition().x,
                                 object.getPosition().y,
                                 object.getGlobalBounds().width,
                                 object.getGlobalBounds().height);

            if(tempRect.contains(sf::Mouse::getPosition(window))){
                return true;
            }
        }

        return false;
    }

    bool InputManager::IsSpriteHovered(sf::Sprite object, sf::RenderWindow &window) {

        sf::IntRect tempRect(object.getPosition().x,
                             object.getPosition().y,
                             object.getGlobalBounds().width,
                             object.getGlobalBounds().height);

        return tempRect.contains(sf::Mouse::getPosition(window));
    }

    int InputManager::GetCurrentSprite(std::map<int, sf::Sprite> &buttons,
                                       int &currentSprite,
                                       bool mouseMoved,
                                       bool up,
                                       bool down,
                                       sf::RenderWindow &window){

        if(mouseMoved){
            for(const auto &it: buttons){
                if(IsSpriteHovered(it.second, window)){
                    currentSprite = it.first;
                }
            }
        }

        // Checks for upper and lower bounds
        if(up) if(currentSprite > 0) currentSprite--;
        if(down) if(currentSprite < buttons.size() - 1) currentSprite++;

        return currentSprite;
    }
}