#include "game.h"
#include "States/splash_state.h"
#include "plog/Log.h"

namespace Kjeledyr{

    Game::Game(unsigned int width, unsigned int height, std::string title){

#if (defined (LINUX) || defined (__linux__))
        data->window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
#elif (defined (_WIN32) || defined (_WIN64))
        data->window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
#elif defined(__APPLE__) && defined(__MACH__)
        data->window.create(sf::VideoMode(width, height), title, sf::Style::Resize);
#else data->window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
#endif
        data->window.setVerticalSyncEnabled(true);

        plog::init(plog::debug, "Debug.txt");

        /// This line decides which state the game opens in
        data->stateMachine.AddState(StateRef(new SplashState(this->data)));
        LOGD<<"Program Window Opened";
        this->Run();
    }

    // The game loop runs while the window is open
    void Game::Run(){
        LOGD<<"Gameloop started";
        float newTime, frameTime, interpolation;

        float currentTime = this->frameClock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while(this->data->window.isOpen()){

            this->data->stateMachine.ProcessStateChanges();

            // The frame time between frames might vary.
            // Handling this by setting an upper limit to ensure smooth gameplay.
            newTime = this->frameClock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;
            if(frameTime > 0.25f) frameTime = 0.25f;
            currentTime = newTime;
            accumulator += frameTime; // Adds the frame time to the average

            /* If accumulator < delta, the new frametime that was just added
             * to the average frametime variable 'accumulator' is so small that
             * nothing could've happened since the last frametime. That means that
             * there is no need to check for inputs or updates in the current state.*/
            while(accumulator >= delta){
                this->data->stateMachine.GetActiveState()->HandleInput();
                this->data->stateMachine.GetActiveState()->Update(delta);

                accumulator -= delta;
            }

            // Interpolation ensures that animation objects move at the same speed regardless of machine power
            interpolation = accumulator / delta;
            this->data->stateMachine.GetActiveState()->Draw(interpolation);
        }
    }

}