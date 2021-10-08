#ifndef KJELEDYR_SPLASH_STATE_H
#define KJELEDYR_SPLASH_STATE_H

#include <SFML/Graphics.hpp>

#include "Game Engine/state.h"
#include "Game Engine/game.h"
#include <Player/PlayerObject.h>

namespace Kjeledyr {

    class SplashState : public State {
    public:
        SplashState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float delta);
        void Draw(float delta);

    protected:
        GameDataRef data;

        sf::Clock _clock;

        sf::Texture _backgroundTexture;
        sf::Sprite background;
        PlayerObject player;
    };
}

#endif