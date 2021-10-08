#include <iostream>
#include <SFML/Audio.hpp>
#include <fstream>

#include "DEFINITIONS.h"
#include "Game Engine/game.h"

int main() {
    Kjeledyr::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Pot Pets");
    std::ofstream ofs;
    ofs.open("Debug.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    return EXIT_SUCCESS;
}