#ifndef KJELEDYR_DEFINITIONS_H
#define KJELEDYR_DEFINITIONS_H

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define TILE_SIZE 64

#define SPLASH_STATE_SHOW_TIME 3.0

#define PLAYER_WIDTH 96
#define PLAYER_HEIGHT 96
#define JUMP_SPEED (-20)

#define PLAYER_XSPEED 10

#define DOWN_LEFT 55
#define UP_LEFT 57
#define UP_RIGHT 58
#define DOWN_RIGHT 56

#define JOYSTICK_UP sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100
#define JOYSTICK_DOWN sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100
#define JOYSTICK_RIGHT sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100
#define JOYSTICK_LEFT sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100
#define JOYSTICK1_A sf::Joystick::isButtonPressed(0,0)
#define JOYSTICK2_A sf::Joystick::isButtonPressed(1,0)
#define JOYSTICK3_A sf::Joystick::isButtonPressed(2,0)
#define JOYSTICK4_A sf::Joystick::isButtonPressed(3,0)
#define JOYSTICK1_B sf::Joystick::isButtonPressed(0,1)
#define JOYSTICK1_X sf::Joystick::isButtonPressed(0,2)

// Splash State filepaths
#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/SplashState/Loading.png"

// Menu State filepaths
#define MENU_BACKGROUND_FILEPATH "Resources/res/MenuState/MenuBackground.png"
#define POTPETS_TITLE_FILEPATH "Resources/res/MenuState/PotPetsTitle.png"
#define MENU_PLAY_BUTTON_FILEPATH "Resources/res/MenuState/Play.png"
#define MENU_PLAY_PRESSEDBUTTON_FILEPATH "Resources/res/MenuState/PlayPressed.png"
#define MENU_HIGHSCORE_BUTTON_FILEPATH "Resources/res/MenuState/Highscore.png"
#define MENU_HIGHSCORE_PRESSEDBUTTON_FILEPATH "Resources/res/MenuState/HighscorePressed.png"
#define MENU_EXIT_BUTTON_FILEPATH "Resources/res/MenuState/Exit.png"
#define MENU_EXIT_PRESSEDBUTTON_FILEPATH "Resources/res/MenuState/ExitPressed.png"
#define MENU_SETTINGS_BUTTON_FILEPATH "Resources/res/MenuState/Settings.png"
#define MENU_SETTINGS_PRESSEDBUTTON_FILEPATH "Resources/res/MenuState/SettingsPressed.png"
#define MENU_SOUND_BUTTON_FILEPATH "Resources/res/MenuState/Sound.png"
#define MENU_SOUND_PRESSEDBUTTON_FILEPATH "Resources/res/MenuState/SoundPressed.png"
#define MENU_MUTE_BUTTON_FILEPATH "Resources/res/MenuState/Mute.png"
#define MENU_MUTE_PRESSEDBUTTON_FILEPATH "Resources/res/MenuState/MutePressed.png"

// Game over state filepaths
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/res/GameOverState/GameOverBackground.png"
#define NEW_HIGHSCORE_BACKGROUND_FILEPATH "Resources/res/GameOverState/GameOver_EnterHighscore.png"
#define OK_BUTTON_FILEPATH "Resources/res/GameOverState/OKButton.png"
#define OK_BUTTON_PRESSED_FILEPATH "Resources/res/GameOverState/OKPressed.png"
#define MENU_BUTTON_FILEPATH "Resources/res/GameOverState/MenuButton.png"
#define MENU_BUTTON_PRESSED_FILEPATH "Resources/res/GameOverState/MenuButtonPressed.png"
#define HIGHSCORES_BUTTON_FILEPATH "Resources/res/GameOverState/HighscoreButton.png"
#define HIGHSCORES_BUTTON_PRESSED_FILEPATH "Resources/res/GameOverState/HighscoreButtonPressed.png"

// Highscore state filepaths
#define HIGHSCORE_BACKGROUND_FILEPATH "Resources/res/HighscoreState/HighscoreBackground.png"
#define HIGHSCORE_MENU_BUTTON_FILEPATH "Resources/res/HighscoreState/Menu.png"
#define HIGHSCORE_MENU_PRESSEDBUTTON_FILEPATH "Resources/res/HighscoreState/MenuPressed.png"
#define HIGHSCORE_SINGLEPLAYER_BUTTON_FILEPATH "Resources/res/HighscoreState/Singleplayer.png"
#define HIGHSCORE_SINGLEPLAYER_PRESSEDBUTTON_FILEPATH "Resources/res/HighscoreState/SingleplayerPressed.png"
#define HIGHSCORE_MULTIPLAYER_BUTTON_FILEPATH "Resources/res/HighscoreState/Multiplayer.png"
#define HIGHSCORE_MULTIPLAYER_PRESSEDBUTTON_FILEPATH "Resources/res/HighscoreState/MultiplayerPressed.png"

// Settings state filepaths
#define SETTINGS_SCENE_BACKGROUND_FILEPATH "Resources/res/SettingState/SettingsBackground.png"
#define SETTINGS_CONTROLLER_GUIDE_FILEPATH "Resources/res/SettingState/ControllerGuide.png"
#define SETTINGS_BACK_BUTTON_FILEPATH "Resources/res/SettingState/BackButton.png"
#define SETTINGS_BACK_PRESSEDBUTTON_FILEPATH "Resources/res/SettingState/BackButtonPressed.png"
#define VOLUME_BAR_FILEPATH "Resources/res/SettingState/VolumeBar.png"
#define HOVERED_LEFT_BUTTON_FILEPATH "Resources/res/SettingState/hovered-left-button.png"
#define HOVERED_RIGHT_BUTTON_FILEPATH "Resources/res/SettingState/hovered-right-button.png"
#define LEFT_CLICKED_FILEPATH "Resources/res/left-button.png"
#define RIGHT_CLICKED_FILEPATH "Resources/res/right-button.png"

// Character select state filepaths
#define CHAR_SCENE_BACKGROUND_FILEPATH "Resources/res/CharSelectState/CharSelectBackground.png"
#define CHAR_BUNNY_FILEPATH "Resources/res/CharSelectState/Bunny.png"
#define CHAR_KATT_FILEPATH "Resources/res/CharSelectState/Katt.png"
#define CHAR_HUND_FILEPATH "Resources/res/CharSelectState/Hund.png"
#define CHAR_PIG_FILEPATH "Resources/res/CharSelectState/Pig.png"
#define LEFT_BUTTON_FILEPATH "Resources/res/CharSelectState/left-button.png"
#define RIGHT_BUTTON_FILEPATH "Resources/res/CharSelectState/right-button.png"
#define READY_FILEPATH "Resources/res/CharSelectState/Ready2.png"
#define PRESSTOPLAY_FILEPATH "Resources/res/CharSelectState/PressToPlay2.png"
#define JOIN_FILEPATH "Resources/res/CharSelectState/PressToJoin.png"

// Level select state filepaths
#define LEVELSELECT_BACKGROUND_FILEPATH "Resources/res/LevelSelectState/LevelSelectBackground.png"
#define LEVELSELECT_LEVEL1_FILEPATH "Resources/res/LevelSelectState/Level1.png"
#define LEVELSELECT_LEVEL2_FILEPATH "Resources/res/LevelSelectState/Level2.png"
#define LEVELSELECT_LEVEL3_FILEPATH "Resources/res/LevelSelectState/Level3.png"

#define PLAYER_TILESET_FILEPATH "Resources/res/PlayerTileSet.png"
#define POWERUPS_FILEPATH "Resources/res/PowerUps.png"
#define GOLDEN_TILESET_FILEPATH "Resources/res/GoldenTileSet.png"


#define BUNNYHEAD_FILEPATH "Resources/res/Bunnyhead.png"
#define CATHEAD_FILEPATH "Resources/res/Cathead.png"
#define DOGHEAD_FILEPATH "Resources/res/Doghead.png"
#define PIGHEAD_FILEPATH "Resources/res/Pighead.png"

// Music
#define MENU_MUSIC_FILEPATH "Resources/res/Music/music.ogg"
#define GAME_MUSIC_FILEPATH "Resources/res/Music/gamemusic.ogg"
#define LEVEL2_MUSIC_FILEPATH "Resources/res/Music/It_Takes_Two_to_Tango.ogg"
#define LEVEL3_MUSIC_FILEPATH "Resources/res/Music/Up_on_a_Housetop.ogg"


// Fonts
#define BERLIN_SANS_FB_FILEPATH "Resources/res/Fonts/BRLNSDB.TTF"
#define GEORGIA_FONT_FILEPATH "Resources/res/Fonts/GEORGIA.TTF"

#endif