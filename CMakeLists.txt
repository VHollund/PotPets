cmake_minimum_required(VERSION 3.8)
project(kjeledyr)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES "main.cpp" "Game Engine/state.h" "Game Engine/statemachine.h" "Game Engine/statemachine.cpp" "Game Engine/asset_manager.cpp" "Game Engine/asset_manager.h" "Game Engine/input_manager.cpp" "Game Engine/input_manager.h" "Game Engine/game.cpp" "Game Engine/game.h" "DEFINITIONS.h" "States/menu_state.cpp" "States/menu_state.h" "States/splash_state.cpp" "States/splash_state.h" "States/game_state.cpp" "States/game_state.h" "Player/player.cpp" "Player/player.h" "States/highscore_state.cpp" "States/highscore_state.h" "Player/PlayerObject.h" "Map/layer.cpp" "Map/layer.h" "Map/map.cpp" "Map/map.h" "Map/object.cpp" "Map/object.h" "Map/sprite.cpp" "Map/sprite.h" "Player/AiPlayer.cpp" "Player/AiPlayer.h" "Game Elements/AiRoutes.cpp" "Game Elements/AiRoutes.h" "States/settings_state.cpp" "States/settings_state.h" "Game Elements/backgroundAnimations.cpp" "Game Elements/backgroundAnimations.h" "States/charselect_state.cpp" "States/charselect_state.h" "Game Elements/powerUp.cpp" "Game Elements/powerUp.h" "States/levelselect_state.cpp" "States/levelselect_state.h" "Game Elements/bullet.cpp" "Game Elements/bullet.h" "Game Elements/ammo.cpp" "Game Elements/ammo.h" "States/game_over_state.cpp" "States/game_over_state.h" "States/highscore_state.cpp" "States/highscore_state.h" "Game Elements/Playerstruct.h")

add_executable(kjeledyr ${SOURCE_FILES})
target_link_libraries(kjeledyr sfml-graphics sfml-audio sfml-window sfml-system jsoncpp)
target_include_directories(kjeledyr PUBLIC plog/include .)