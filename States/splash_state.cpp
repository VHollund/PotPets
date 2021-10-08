#include "splash_state.h"
#include "States/menu_state.h"
#include <plog/Log.h>

namespace Kjeledyr{

    SplashState::SplashState(GameDataRef data) : data(data) {}

    void SplashState::Init() {
        player.SetSpriteOffSet(2);
        player.SetSprite(160,800,PLAYER_WIDTH,PLAYER_HEIGHT);

        data->assetManager.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

        background.setTexture(this->data->assetManager.GetTexture("Splash State Background"));

        //Initializing menu
        data->assetManager.LoadTexture("Menu Background", MENU_BACKGROUND_FILEPATH);
        data->assetManager.LoadTexture("Title", POTPETS_TITLE_FILEPATH);
        data->assetManager.LoadTexture("Play Button", MENU_PLAY_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Play Button Pressed", MENU_PLAY_PRESSEDBUTTON_FILEPATH);
        data->assetManager.LoadTexture("Highscore Button", MENU_HIGHSCORE_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Highscore Button Pressed", MENU_HIGHSCORE_PRESSEDBUTTON_FILEPATH);
        data->assetManager.LoadTexture("Exit Button", MENU_EXIT_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Exit Button Pressed", MENU_EXIT_PRESSEDBUTTON_FILEPATH);
        data->assetManager.LoadTexture("Settings Button", MENU_SETTINGS_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Settings Button Pressed", MENU_SETTINGS_PRESSEDBUTTON_FILEPATH);
        data->assetManager.LoadTexture("Sound Button", MENU_SOUND_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Sound Button Pressed", MENU_SOUND_PRESSEDBUTTON_FILEPATH);
        data->assetManager.LoadTexture("Mute Button", MENU_MUTE_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Mute Button Pressed", MENU_MUTE_PRESSEDBUTTON_FILEPATH);
        data->assetManager.LoadMusic("Music", MENU_MUSIC_FILEPATH);

        // Initializing game
        data->assetManager.LoadMusic("Game Music", GAME_MUSIC_FILEPATH);
        data->assetManager.LoadTexture("PowerUps", POWERUPS_FILEPATH);
        data->assetManager.LoadMusic("Christmas Music", LEVEL3_MUSIC_FILEPATH);
        data->assetManager.LoadMusic("Kitchen Music", LEVEL2_MUSIC_FILEPATH);

        //Playerobject
        data->assetManager.LoadTexture("Player Tileset", PLAYER_TILESET_FILEPATH);
        data->assetManager.LoadTexture("Golden Tileset", GOLDEN_TILESET_FILEPATH);

        // Initializing highscore assets
        data->assetManager.LoadTexture("Highscore State Background", HIGHSCORE_BACKGROUND_FILEPATH);
        data->assetManager.LoadTexture("Back Button", HIGHSCORE_MENU_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Back Pressed", HIGHSCORE_MENU_PRESSEDBUTTON_FILEPATH);
        data->assetManager.LoadTexture("Singleplayer Button", HIGHSCORE_SINGLEPLAYER_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Singleplayer Pressed", HIGHSCORE_SINGLEPLAYER_PRESSEDBUTTON_FILEPATH);
        data->assetManager.LoadTexture("Multiplayer Button", HIGHSCORE_MULTIPLAYER_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Multiplayer Pressed", HIGHSCORE_MULTIPLAYER_PRESSEDBUTTON_FILEPATH);

        // Initializing game over assets
        data->assetManager.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
        data->assetManager.LoadTexture("New Highscore Background", NEW_HIGHSCORE_BACKGROUND_FILEPATH);
        data->assetManager.LoadTexture("Menu button", MENU_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Menu button pressed", MENU_BUTTON_PRESSED_FILEPATH);
        data->assetManager.LoadTexture("Highscore button", HIGHSCORES_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Highscore button pressed", HIGHSCORES_BUTTON_PRESSED_FILEPATH);
        data->assetManager.LoadTexture("OK", OK_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("OK pressed", OK_BUTTON_PRESSED_FILEPATH);

        // Initializing character heads
        data->assetManager.LoadTexture("BunnyHead", BUNNYHEAD_FILEPATH);
        data->assetManager.LoadTexture("CatHead", CATHEAD_FILEPATH);
        data->assetManager.LoadTexture("DogHead", DOGHEAD_FILEPATH);
        data->assetManager.LoadTexture("PigHead", PIGHEAD_FILEPATH);

        // Initializing character select assets
        data->assetManager.LoadTexture("Char State Background", CHAR_SCENE_BACKGROUND_FILEPATH);
        data->assetManager.LoadTexture("Bunny", CHAR_BUNNY_FILEPATH);
        data->assetManager.LoadTexture("Cat", CHAR_KATT_FILEPATH);
        data->assetManager.LoadTexture("Dog", CHAR_HUND_FILEPATH);
        data->assetManager.LoadTexture("Pig", CHAR_PIG_FILEPATH);
        data->assetManager.LoadTexture("Left button", LEFT_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Right button", RIGHT_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Hovered Left button", HOVERED_LEFT_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Hovered Right button", HOVERED_RIGHT_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Press to play", PRESSTOPLAY_FILEPATH);
        data->assetManager.LoadTexture("Join", JOIN_FILEPATH);
        data->assetManager.LoadTexture("Ready", READY_FILEPATH);

        // Initializing level select assets
        data->assetManager.LoadTexture("Level State Background", LEVELSELECT_BACKGROUND_FILEPATH);
        data->assetManager.LoadTexture("Level 1", LEVELSELECT_LEVEL1_FILEPATH);
        data->assetManager.LoadTexture("Level 2", LEVELSELECT_LEVEL2_FILEPATH);
        data->assetManager.LoadTexture("Level 3", LEVELSELECT_LEVEL3_FILEPATH);

        // Initializing settings assets
        data->assetManager.LoadTexture("Settings Menu", SETTINGS_SCENE_BACKGROUND_FILEPATH);
        data->assetManager.LoadTexture("Settings Back Button", SETTINGS_BACK_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Settings Back Pressed Button", SETTINGS_BACK_PRESSEDBUTTON_FILEPATH);
        data->assetManager.LoadTexture("Volume Bar", VOLUME_BAR_FILEPATH);
        data->assetManager.LoadFont("Georgia", GEORGIA_FONT_FILEPATH);
        data->assetManager.LoadTexture("Left Hovered", HOVERED_LEFT_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Right Hovered", HOVERED_RIGHT_BUTTON_FILEPATH);
        data->assetManager.LoadTexture("Controller Guide", SETTINGS_CONTROLLER_GUIDE_FILEPATH);

        // Initializing fonts
        data->assetManager.LoadFont("Berlin Sans FB", BERLIN_SANS_FB_FILEPATH);

        data->levels.emplace_back("1");
        data->levels.emplace_back("2");
        data->levels.emplace_back("3");
        data->levels[0] = "Map/data/bane1.json";
        data->levels[1] = "Map/data/bane2.json";
        data->levels[2] = "Map/data/bane3.json";

        data->chosenSprite.reserve(4);
    }

    void SplashState::HandleInput() {}

    void SplashState::Update(float delta) {
        if(_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
                LOGD<<"Going to MenuState";
            data->stateMachine.AddState(StateRef(new MenuState(this->data)));
        }

        player.SetX(player.GetX() + 11);
        player.AnimationRight();
        player.PlayAnimation();

    }

    void SplashState::Draw(float delta) {
        data->window.clear();

        data->window.draw(background);
        data->window.draw(player.DrawSprite());

        data->window.display();
    }
}