#include <DEFINITIONS.h>
#include <iostream>
#include <chrono>
#include <random>
#include "game_state.h"
#include "menu_state.h"
#include "game_over_state.h"
#include <plog/Log.h>


namespace Kjeledyr {

    GameState::GameState(GameDataRef data, bool singleplayer) : data(data), singleplayer(singleplayer) {}

    void GameState::Init() {
        // Load map information from JSON into object list

        mapName = data->levels[data->levelChoice];
        LOGE_IF(!Map::Load(mapName, objects, collisionLayer, collisionTiles, powerUpSpawns, triggerPoints, spawnPoints)) << "Failed to load map data!";

        std::cout.flush();

        for (auto point : triggerPoints) { //reading all triggerpoint in to local storage
            routes.push_back(new AiRoutes(point.first.first, point.first.second, point.second));
        }


        Music();

        backgroundObjects = new backgroundAnimations(data->levelChoice);


        powerUps[0] = new powerUp(PowerType::gun, data);
        powerUps[1] = new powerUp(PowerType::invincible, data);
        powerUps[2] = new powerUp(PowerType::melee, data);
        clock.restart();
        powerTimer = GetRandomNumber(pMinTime, pMaxTime);

        font.loadFromFile("Resources/res/Fonts/BRLNSDB.TTF");
        timerText.setFont(font);
        timerText.setCharacterSize(52);
        timerText.setPosition(880, 30);
        int k=0;
        for (int i = 0; i < 4-data->numbersOfAI;++i) { //Create 4-amount of ai players, and initialized with chosen sprite and controller id.
            if(data->playerInfo.find(i)->second->isReady){
                player = new Player(data->chosenSprite[i],spawnPoints);
                player->SetID(k);
                player->SetControllerID(data->playerInfo.find(i)->second->controlID);
                Allplayers[i]=player;
                Players[i]=player;
                k++;
            }
        }

        //
        for (int j = 0; j < data->numbersOfAI; j++) { //create numberOfAI Ai's, initialized with a random sprite
            int rOffSet = rand()%4;
            AIPlayer = new AiPlayer(rOffSet,spawnPoints);
            AIPlayer->SetID(k);
            Allplayers.emplace(Allplayers.size(),AIPlayer);
            data->chosenSprite[(int)Allplayers.size()-1] = rOffSet;
            AIplayers[j] = AIPlayer;
            k++;
        }

        Heads();
        LOGI<<"Game State Initialized";
    }

    void GameState::HandleInput() {
        sf::Event event;
        ///WINDOW AND GAME CONTROLL///////////////////////////////////
        while (data->window.pollEvent(event)) {


            if (event.type == sf::Event::Closed) { //Close on Exit
                data->window.close();
            }

            if (event.type == sf::Event::KeyPressed) {

                // Reloads the map when you press "F5"
                if (event.key.code == sf::Keyboard::F5) { //For bugtesting and possible map reload press F5
                    objects.clear();
                    LOGE_IF(!Map::Load(mapName, objects, collisionLayer, collisionTiles, powerUpSpawns, triggerPoints,
                                       spawnPoints))
                        << "Failed to reload map data.";
                }
            }
        }
        // Goes back to menu when you press "Esc"
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 3)) {
            data->music->stop();
            LOGI<<"Gamestate To Menu";
            data->stateMachine.AddState(StateRef(new MenuState(this->data)));
        }

        ///Joystick Movement//////////////////////////
        for(auto playable:Players){ //Handle the Joystick input for all players
            playable.second->HandleInput(Allplayers,data);
        }
        ///Keyboardinputs for Player 1//////////////
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (Allplayers.find(0)->second->GetX() < SCREEN_WIDTH - PLAYER_WIDTH) {
                Allplayers.find(0)->second->SetXSpeed(PLAYER_XSPEED);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (Allplayers.find(0)->second->GetX() > 10) {
                Allplayers.find(0)->second->SetXSpeed(-PLAYER_XSPEED);
            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            Allplayers.find(0)->second->Jump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            Allplayers.find(0)->second->CheckAttack(Allplayers, data);
        }
    }

    void GameState::Update(float delta) {

        for (auto ai:AIplayers) { //For all Ai players run the relevant functions
            if (ai.second->CheckIfTrapped()) {
                ai.second->FindRoute(routes);
            } else {
                ai.second->findTarget(Allplayers);
                ai.second->moveDir(routes, Allplayers);
            }
        }

        for (auto obj:Allplayers) { //for All playerObject run relevant functions in playerObjecct.h
            obj.second->Move(); //Movement
            obj.second->CollisionDetection(collisionTiles); //Collision
            obj.second->Gravity(); //Gravity
            obj.second->CheckAnimation(); //Check what playerObject is currently doing
            obj.second->PlayAnimation(); //Play animation accoardingly
            obj.second->CheckRespawn(spawnPoints,Allplayers);

            if (currentPower != nullptr) { //if powerup is on the map
                if (obj.second->CheckPowerUpCollision(*currentPower)) { //check how long it as been there
                    currentPower = nullptr; //if relevant remove the powerup
                    clock.restart(); //and restart the powerup timer
                }
            }
            obj.second->PowerUpTick(); //Tick the powerup

            obj.second->CheckJumpCollision(Allplayers); //is the playerObject landing on someone?
            if(obj.second->GetState() == PlayerStates::invincible) obj.second->CheckInvincibleCollision(Allplayers); //If player is imortal, check if someone should die.
            if(obj.second->IsBulletInAir()) obj.second->BulletTick(collisionTiles, Allplayers);// if a bullet is in the air, tick it
            Gametime(); //Tick the game time
            GameScore(); //tick possible Gamescore


            if (obj.second->GetState() == PlayerStates::gun) { obj.second->AmmoTick(); }
        }
        backgroundObjects->tick(); //Tick background objects
        SpawnPowerUp(); //Spawn powerp if relevant
    }

    void GameState::Draw(float delta) {
        data->window.clear(); //Clear screen
        data->window.draw(_background); //Draw Background

        drawBackgroundObjects = true;
        for (Object *object : objects) //Draws the whole map and process animations etc from tiled.
        {
            object->process(delta);
            object->draw(data->window);

            if (drawBackgroundObjects) {
                for (int i = 0; i < backgroundObjects->GetAllObjectsSize(); ++i) {
                    data->window.draw(backgroundObjects->GetObject(i).DrawSprite());
                }
            }
            drawBackgroundObjects = false;
        }

        for (auto obj:Allplayers) { //Draw all playerObjects
            data->window.draw(obj.second->DrawSprite());

            //Draws the ammo on the player
            if (obj.second->GetState() == PlayerStates::gun) {
                data->window.draw(obj.second->DrawPowerIcon());
                for (auto ammo : obj.second->GetTotalAmmo()) { data->window.draw(ammo->rect); }
            }
            //Draws the bullet when the player shoots
            if (obj.second->IsBulletInAir()) data->window.draw(obj.second->DrawBullet());

            if (obj.second->GetState() == PlayerStates::melee) {
                data->window.draw(obj.second->DrawPowerIcon());
            }
        }

        if (currentPower != nullptr) data->window.draw(currentPower->DrawSprite()); //Draw PowerUp

        data->window.draw(timerText); //Draw Timer
        for(auto charHead : charHeads) data->window.draw(charHead); //Draw score and score heads
        for(auto scoreText : scoreTexts) data->window.draw(scoreText);

        data->window.display();
    }

    int GameState::GetRandomNumber(int min, int max) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }

    void GameState::SpawnPowerUp() {
        //if(currentPower == nullptr) { // can be used if we dont spawned powerups to respawn at new location
        if (clock.getElapsedTime().asSeconds() > powerTimer) {
            int newPowerUp = GetRandomNumber(0, powerUps[0]->allPowerUpsCount - 1);
            currentPower = powerUps[newPowerUp];
            powerUps[newPowerUp]->SetRandomSpawn(powerUpSpawns);
            clock.restart();
            powerTimer = GetRandomNumber(pMinTime, pMaxTime);
        }
        //}
    }

    void GameState::Gametime() {

        if(gameClock.getElapsedTime().asSeconds()>=1){
            timer4--;
            if(timer4 < 0){
                timer3--;
                timer4 = 9;
                if(timer3<0){
                    timer2--;
                    timer3 = 5;
                    if(timer2<0){
                        timer1--;
                        timer2 = 9;
                        if(timer1<0){
                           GotoGameOver();
                        }
                    }
                }
            }

            gameClock.restart();
        }

        timers = std::to_string(timer1) + std::to_string(timer2) + " : " + std::to_string(timer3) +
                 std::to_string(timer4);
        timerText.setString(timers);

    }

    void GameState::GotoGameOver() {
        int topScore = 0;
        int id = 0;
        for (auto player : Allplayers){
            if(player.second->GetScore()>topScore && !player.second->GetAI()){
                topScore = player.second->GetScore();
                id = player.first;
            }
        }
        int winner = Allplayers[id]->GetID();
        data->music->stop();
        LOGI<<"GameState to Game Over State";
        data->stateMachine.AddState(StateRef(new GameOverState(this->data, topScore, winner, this->singleplayer)));
    }

    void GameState::GameScore() {
        for (int i = 0; i < Allplayers.size() ; ++i) {
            scoreTexts[i].setString(std::to_string(Allplayers[i]->GetScore()));
        }
    }

    void GameState::Heads() {
            sf::Text scoreText;
            scoreText.setFont(data->assetManager.GetFont("Berlin Sans FB"));
            scoreText.setCharacterSize(52);
            if(data->levelChoice == 1) scoreText.setColor(sf::Color::Black);

            for (int i = 0; i < Allplayers.size() ; ++i) {
                sf::Sprite temp;
                temp.setTexture(*SetHeadTexture(data->chosenSprite[i]).getTexture());

                charHeads.push_back(temp);
                scoreTexts.push_back(scoreText);
            }
            auto playerSize = Allplayers.size();
            if(playerSize>0) {
                charHeads[0].setPosition(150,10);
                scoreTexts[0].setPosition(250,30);
            }
            if(playerSize>1) {
                charHeads[1].setPosition(500,10);
                scoreTexts[1].setPosition(600,30);
            }
            if(playerSize>2) {
                charHeads[2].setPosition(1300,10);
                scoreTexts[2].setPosition(1400,30);
            }
            if(playerSize>3) {
                charHeads[3].setPosition(1600,10);
                scoreTexts[3].setPosition(1700,30);
            }
    }

    sf::Sprite GameState::SetHeadTexture(int spriteOffSet) {
        sf::Sprite temp;
        if(spriteOffSet==0) temp.setTexture(data->assetManager.GetTexture("BunnyHead"));
        if(spriteOffSet==1) temp.setTexture(data->assetManager.GetTexture("CatHead"));
        if(spriteOffSet==2) temp.setTexture(data->assetManager.GetTexture("DogHead"));
        if(spriteOffSet==3) temp.setTexture(data->assetManager.GetTexture("PigHead"));
        return temp;
    }

    void GameState::Music() {
        if(data->levelChoice == 0){
            data->music = data->assetManager.GetMusic("Game Music");
            if (data->isSoundOn) {
                data->music->play();
                data->music->setVolume(data->volumeMusic);
                data->music->setLoop(true);
            }
            LOGI << "Playing music for the Bright Forest map";
        }

        if(data->levelChoice == 1){
            timerText.setColor(sf::Color::Black);
            data->music = data->assetManager.GetMusic("Kitchen Music");
            if (data->isSoundOn) {
                data->music->play();
                data->music->setVolume(data->volumeMusic);
                data->music->setLoop(true);
            }
            LOGI << "Playing music for the Kitchen map";
        }

        if(data->levelChoice == 2){
            data->music = data->assetManager.GetMusic("Christmas Music");
            if (data->isSoundOn) {
                data->music->play();
                data->music->setVolume(data->volumeMusic);
                data->music->setLoop(true);
            }
            LOGI << "Playing music for the Christmas map";
        }
    }
}


