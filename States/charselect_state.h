#ifndef KJELEDYR_CHARSELECT_STATE_H
#define KJELEDYR_CHARSELECT_STATE_H

#include <Game Engine/state.h>
#include <Game Engine/game.h>
#include "Game Elements/Playerstruct.h"

namespace Kjeledyr {
    class CharSelectState : public State {

    public:
        CharSelectState(GameDataRef data);
        void Init();
        void HandleInput();
        void Update(float delta);
        void Draw(float delta);
        void GoToLevelState(); //Used to store all necessary data before going to GameState
        void IsHovered();
        int GetPlayersConnected(); //returns how many players which are connected
        void CheckAISelected();
        void CheckOtherCharactersSelected(std::map<int, bool> &takenChar); //selects the next available character

    protected:
        GameDataRef data;

        //The mouse is not moved at the start of the game
        bool mouseMoved = false;
        //True = singlePlayer, false = multiplayer
        bool singlePlayer = true;
        sf::Font font; //Font for the CharacterSelect
        sf::Sprite charBackground; // Background
        std::vector<sf::Sprite> buttons;
        long long int buttonChoice;
        std::map<int, bool> takenChar; // Map which stores if a character is taken or not.
        sf::Clock clockJoystick; // Used to time the joystick input, prevent clicking X 10 times a second etc..
        int minTimeJoystick = 200;
        std::vector<sf::Int32> lastTimePressed; // stores the last time a button was pressed

        //Struct with all 4 players and their assets
        struct players *player1,*player2,*player3,*player4;

        std::vector<players*> allPlayers; // A vector for all the players
    };

}

#endif //KJELEDYR_CHARSELECT_STATE_H