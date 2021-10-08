#ifndef KJELEDYR_ASSET_MANAGER_H
#define KJELEDYR_ASSET_MANAGER_H

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// The Asset Manager handles all resources.

namespace Kjeledyr {

    class AssetManager {
    public:
        AssetManager(){}
        ~AssetManager(){}

        void LoadTexture(std::string name, std::string fileName);
        sf::Texture &GetTexture(std::string name);
        void LoadFont(std::string name, std::string fileName);
        sf::Font &GetFont(std::string name);
        void LoadMusic(std::string name, std::string fileName);
        sf::Music *GetMusic(std::string name);

    protected:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font> fonts;
        std::map<std::string, sf::Music*> music;
    };
}


#endif