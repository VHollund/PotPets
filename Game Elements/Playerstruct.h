#ifndef KJELEDYR_PLAYERSTRUCT_H
#define KJELEDYR_PLAYERSTRUCT_H


#include <map>


namespace Kjeledyr {

struct players {
        players();

        void LeftControl(int playersConnected, std::map<int, bool> &takenChar);

        void RightControl(int playersConnected, std::map<int, bool> &takenChar);

        void SecondLeftControl(std::map<int, bool> &takenChar);

        void SecondRightControl(std::map<int, bool> &takenChar);

        void Player1Enter(std::map<int, bool> &takenChar);

        void PlayersEnter(std::map<int, bool> &takenChar);

        void Player1Back(std::map<int, bool> &takenChar);

        void PlayersBack(std::map<int, bool> &takenChar);

        void IsHoveredfalse();

        bool isHoveredLeft = false;
        bool isHoveredRight = false;

        std::map<int, sf::Sprite> charSelect;
        std::vector <sf::Text> AINumbers;
        std::vector <sf::Text> charNames;

        typedef std::vector <sf::Sprite> Characters;
        Characters characters;
        sf::Sprite bunny;
        sf::Sprite cat;
        sf::Sprite dog;
        sf::Sprite pig;
        sf::Sprite leftButton;
        sf::Sprite rightButton;
        sf::Sprite hoveredLeftButton;
        sf::Sprite hoveredRightButton;

        sf::Sprite ready;
        sf::Sprite pressToPlay;
        sf::Sprite join;

        sf::Text chInfo;
        sf::Text opInfo;

        sf::Text Bunny;
        sf::Text Cat;
        sf::Text Dog;
        sf::Text Pig;

        sf::Text aiNumber0;
        sf::Text aiNumber1;
        sf::Text aiNumber2;
        sf::Text aiNumber3;
    
        long long int charChoice = 0;
        long long int AIChoice = 0;
        long long int nameChoice = 0;

        int id; // player1 got id = 0, player2 got id = 1, and so on. Useful in ranged loops etc.

        int enterCount;
        unsigned int controlID;

        bool left = false;
        bool right = false;
        bool isCharConnected = false;
        bool isReady = false;
        bool isAISelected = false;
    };
}
#endif //KJELEDYR_PLAYERSTRUCT_H
