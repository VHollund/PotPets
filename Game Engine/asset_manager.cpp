#include <plog/Log.h>
#include "asset_manager.h"

namespace Kjeledyr {

    /**
     * Loads a texture from the resources folder and stores it in a texture map.
     *
     * @param name Texture name of your own choosing
     * @param fileName The texture name's path name, @see DEFINITIONS.h
     */
    void AssetManager::LoadTexture(std::string name, std::string fileName){
        sf::Texture texture;

        if(texture.loadFromFile(fileName)){
            this->textures[name] = texture;
            LOGI<<"Loaded: "<<name;
        }else{LOGF<<"Failed to Load:"<<name;}
    }

    /**
     * A getter function for textures.

     * @param name The texture's name
     * @return A texture referance from the map _textures
     */
    sf::Texture &AssetManager::GetTexture(std::string name) {
        if(this->textures.find(name) == this->textures.end())
            LOGF << "Failed to find texture: " << name;
        return this->textures.at(name);
    }

    /**
     * Loads a font from the resources folder and stores it in a font map.
     *
     * @param name Font name of your own choosing
     * @param fileName The font name's path name, @see DEFINITIONS.h
     */
    void AssetManager::LoadFont(std::string name, std::string fileName){
        sf::Font font;

        if(font.loadFromFile(fileName)){
            this->fonts[name] = font;
            LOGI<<"Loaded: "<<name;
        }else{LOGE << "Failed to Load:"<<name;}
    }

    /**
     * A getter function for fonts.
     *
     * @param name The font's name
     * @return A font referance from the map _fonts
     */
    sf::Font &AssetManager::GetFont(std::string name) {
        if(this->fonts.find(name) == this->fonts.end())
            LOGF << "Failed to find font: " << name;
        return this->fonts.at(name);
    }

    void AssetManager::LoadMusic(std::string name, std::string fileName) {
        sf::Music* music = new sf::Music();
        if (music->openFromFile(fileName)){
            this->music[name] = music;
            LOGI<<"Loaded: "<<name;
        }else{LOGE<<"Failed to Load: "<<name;}

    }

    sf::Music *AssetManager::GetMusic(std::string name) {
        if(this->music.find(name) == this->music.end())
            LOGF << "Failed to find song: " << name;
        return this->music.at(name);
    }

}