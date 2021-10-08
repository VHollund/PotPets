#ifndef KJELEDYR_PLAYEROBJECT_H
#define KJELEDYR_PLAYEROBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <DEFINITIONS.h>
#include <Map/object.h>
#include <Map/sprite.h>
#include <Map/map.h>
#include <Game Engine/game.h>
#include <Game Elements/powerUp.h>
#include <Game Elements/bullet.h>
#include <Game Elements/ammo.h>
#include <random>
#include <chrono>

namespace Kjeledyr {

    enum class PlayerStates { normal, gun, invincible, melee};

    class PlayerObject {
    public:

        PlayerObject(){

            playerTileSet = new sf::Texture();
            if (!playerTileSet->loadFromFile("Resources/res/PlayerTileSet.png")) { //Load Player Spritesheet
                std::cout << "FAILED TO LOAD PLAYER SPRITESHEET";
            }
            goldenTileSet = new sf::Texture();
            if(!goldenTileSet->loadFromFile("Resources/res/GoldenTileSet.png")){ //Load tileset for if invincible
                std::cout << "FAILED TO LOAD GOLLDEN TILESET SPRITESHEET" << std::endl;
            }
            sprite.setTexture(*playerTileSet);
            sprite.setTextureRect(sf::IntRect(PLAYER_HEIGHT, 0, -PLAYER_WIDTH, PLAYER_HEIGHT));

            powerUpTileSet = new sf::Texture();
            if(!powerUpTileSet->loadFromFile("Resources/res/PowerUps.png")){ //Load powerup char tileset
                std::cout << "Failed to Load powerupspritesheet" << std::endl;
            }
            powerUpSprite.setTexture(*powerUpTileSet);

            //Defines the size of the collisonrectangles around the player.
            playerLeftRect.setSize(sf::Vector2f(8,PLAYER_HEIGHT-30));
            playerRightRect.setSize(sf::Vector2f(8,PLAYER_HEIGHT-30));
            playerTopRect.setSize(sf::Vector2f(PLAYER_WIDTH-50, 8));
            playerBottomRect.setSize(sf::Vector2f(PLAYER_WIDTH-50, 8));

            playerState = PlayerStates::normal;
            bulletInAir = false;
            bullet = nullptr;
            tileSetChange = false;
            timeDead = 2000;
            Killed();
        }

        void SetX(int x){this->x=x;}
        void SetY(int y){this->y=y;}
        bool GetAI(){return AI;};
        void SetXSpeed(int x){xSpeed=x;}
        void SetYSpeed(int y){ySpeed=y;}
        void SetID(int id){this->id=id;}
        int GetID(){return this->id;}
        int GetYSpeed(){return ySpeed;}
        int GetXSpeed(){return xSpeed;}
        int GetX(){return x;}
        int GetY(){return y;}
        bool IsKilled() {return killed;}
        int GetSpriteOffSet(){ return spriteOffSet;}
        int GetScore(){return score;}
        void SetSpriteOffSet(int offset){spriteOffSet = offset;}
        sf::Sprite GetSprite() {return sprite;}
        PlayerStates GetState(){ return playerState; }

        void CheckRespawn(std::vector<std::pair<int, int>> &spawnPoints, std::map<int,PlayerObject*> allPlayers){ //Checking how long player has been dead, and if dead, should i respawn
            if(killed){
                if (killedClock.getElapsedTime().asMilliseconds() < timeDead) {
                    return;
                }
                else{
                    int randomSpawn = GetRandomNumber(0, (int)spawnPoints.size()-1); //Get a random spawn position out of list
                    this->x = spawnPoints[randomSpawn].first;
                    this->y = spawnPoints[randomSpawn].second;

                    for(auto players:allPlayers){ //if the respawn point is to close to another player, choose another point
                        if(players.second->GetX()>=this->x-10&& players.second->GetX()<this->x+PLAYER_WIDTH+10 &&players.second->GetY()>this->y-20 && players.second->GetY()<this->y+PLAYER_HEIGHT){
                            this->x = spawnPoints[randomSpawn].first;
                            this->y = spawnPoints[randomSpawn].second;
                        }
                    }

                    this->SetYSpeed(0); //Start standing still
                    this->SetXSpeed(0);
                    killed = false;
                }
            }
        }

        ///Animations
        void PlayAnimation() {
            if (clock.getElapsedTime().asMilliseconds() < frameDuration) { //doing this to not rund the animation on max speed, to make it look good
                return;
            }
            if (++frame >= frameCount) {
                frame = 0;

                if (attacking) {
                    attacking = false;
                    AnimationStill();
                    sprite.setOrigin(0, 0);
                }
            }

            clock.restart();
            if (!attacking) { //if not attacking the player will only use its original frame
                sprite.setTextureRect(sf::IntRect((tileX * PLAYER_HEIGHT) + (frame * PLAYER_HEIGHT) + Flipped(),
                                                  (tileY + spriteOffSet * 2) * PLAYER_HEIGHT, FlipAnimation(), PLAYER_HEIGHT));
            }
            else { //if it is attacking it will however use 2x the width
                sprite.setTextureRect(sf::IntRect( tileX * PLAYER_WIDTH + frame * PLAYER_WIDTH * 2 + Flipped() * 2, (tileY + spriteOffSet * 2) * PLAYER_WIDTH, FlipAnimation() * 2, PLAYER_HEIGHT));
                if(!isFlipped)
                    sprite.setOrigin(PLAYER_WIDTH, 0);
            }
        }
        void CheckAnimation(){ //Checking what the player is doing and what it should look like

            if(playerState == PlayerStates::invincible) {
                if (clockBlink.getElapsedTime().asSeconds() > blinkTime) PowerUpBlink();
            }
            else if(sprite.getTexture() != playerTileSet){
                sprite.setTexture(*playerTileSet);
            }

            if (attacking) return;

            else if(CheckStandingStill()){ AnimationStill(); }

            else if(xSpeed>0){
                SetIsFlipped(true);
                if(ySpeed==0) AnimationLeft();
                else if (ySpeed>0 && !collisionBot) AnimationFall();
                else if (ySpeed<0) AnimationJump();
            }
            else if(xSpeed<0){
                SetIsFlipped(false);
                if(ySpeed==0) AnimationRight();
                else if (ySpeed>0 && !collisionBot) AnimationFall();
                else if (ySpeed<0) AnimationJump();
            }

            else if(ySpeed>0 && !collisionBot){ AnimationFall(); }
            else if (ySpeed<0){ AnimationJump(); }

            xOld = x;
            yOld = y;
        }
        bool CheckStandingStill(){
            return (xOld == x) && (yOld == y); //if player standing still
        }
        void AnimationRight(){ //While moving right
            frameCount = 6;
            tileX = 2;
            tileY = 0;
            if(animationID!=0){
                animationID = 0;
                frameDuration = 20;
            }else frameDuration = 70; }
        void AnimationLeft(){ //While moving left

            frameCount = 6;
            tileX = 2;
            tileY = 0;
            if(animationID!=1){
                animationID = 1;
                frameDuration = 20;
            }else frameDuration = 70;}
        void AnimationJump(){ //While Jumping

            frameCount = 2;
            tileX = 8;
            tileY = 0;
            if(animationID!=2){
                animationID = 2;
                frameDuration = 20;
            }else frameDuration = 100;}
        void AnimationFall(){ //While falling

            frameCount = 2;
            tileX = 11;
            tileY = 0;
            if(animationID!=3){
                animationID = 3;
                frameDuration = 50;
            }else frameDuration = 100;}
        void AnimationStill(){ //While standing still
            frameCount = 2;
            tileX = 0;
            tileY = 0;
            if(animationID!=4){
                animationID = 4;
                frameDuration = 20;
            }else frameDuration = 300; }
        void AnimationMeleeAttack(){

            if(!attacking){
                attacking = true;

                frameCount = 15;
                // -1 om for 2 frame animation
                frame = -1;
                tileX = 0;
                tileY = 1;
                frameDuration = 20;
            }
        }
        void KillAnimation(){
            frameCount = 6;
            tileX = 0;
            tileY = 8;
            frameDuration = 20;


        }
        int Flipped(){ //is player going up or down
            if (isFlipped) {
                return PLAYER_HEIGHT;
            }
            else{
                return 0;
            }
        }
        int FlipAnimation(){
            if(isFlipped) {return -PLAYER_WIDTH;}
            else {return PLAYER_WIDTH;}
        }
        void SetIsFlipped(bool isFlipped){
            this->isFlipped = isFlipped;
        }
        ///

        void Gravity(){ //Gravity increases the down wards speed every tick to a max speed of 20 and if collision bot == true, yspeed =0
            if (killed) return;

            if(!collisionBot){
                if(ySpeed<=20) {
                    ySpeed += 1;
                }
            }else{
                ySpeed = 0;
                jumping=false;
                jumpingLeft=false;
                jumpingRight=false;
            }
            if(collisionTop){
                ySpeed = +1;
            }
        }

        void Move(){

            if (killed) return;

            if (jumpingRight && GetX() < SCREEN_WIDTH - PLAYER_WIDTH) SetXSpeed(PLAYER_XSPEED);
            else if (jumpingRight && GetX() >= SCREEN_WIDTH - PLAYER_WIDTH) SetXSpeed(0);

            if (jumpingLeft && GetX() > 10) SetXSpeed(-PLAYER_XSPEED);
            else if (jumpingLeft && GetX() <= 10) SetXSpeed(0);

            x += xSpeed; //on tick x position moves z amount of pixels
            y += ySpeed; //on tick y position moves z amount of pixels
        }

        void Jump() {
            if (killed) return; //Cant Jump if killed

            if(collisionBot) { //Can only Jump while on ground
                ySpeed = JUMP_SPEED; //Jumping sets the y speed to a set speed, which decreases every tick of gravity
                jumping = true;
            }
        }

        void JumpKill(){
            ySpeed = JUMP_SPEED/2; //if landing on someone, bounce with low hight
            jumping = true;
        }

        void SetSprite(int x, int y, int playerwidth, int playerheight){
            this->x = x;
            this->y = y;
            this->playerWidth = PLAYER_WIDTH;
            this->playerHeight = PLAYER_HEIGHT;
            sprite.setPosition(x, y);
        }

        sf::Sprite DrawSprite() {
            SetSprite(GetX(), GetY(), PLAYER_WIDTH, PLAYER_HEIGHT);
            return sprite;
        }

        void CollisionDetection(std::map<std::pair<int, int>, Tile*> &collisionTiles) {

            if(this->y>SCREEN_HEIGHT){
                Killed();
            }

            // Find player coordinates
            int playerLeft = GetX();
            int playerRight = GetX() + PLAYER_WIDTH;
            int playerTop = GetY();
            int playerBottom = GetY() + PLAYER_HEIGHT;

            // Find the four tiles that surrounds the player
            int leftTile = playerLeft / TILE_SIZE;
            int rightTile = playerRight / TILE_SIZE;
            int topTile = playerTop / TILE_SIZE;
            int bottomTile = playerBottom / TILE_SIZE;

            //Sets the posision of the rectangles around the player
            playerLeftRect.setPosition(GetX()+10, GetY()+10);
            playerRightRect.setPosition(GetX()+PLAYER_WIDTH-8 - 10, GetY()+10);
            playerTopRect.setPosition(GetX()+25, GetY());
            playerBottomRect.setPosition(GetX()+25, GetY()+PLAYER_HEIGHT-8);

            collisionBot = false;
            collisionTop = false;
            collisionLeft = false;
            collisionRight = false;


            //Collision for the tiles
            for (int x = leftTile; x <= rightTile; ++x) {
                if(ySpeed>0) {
                    if (collisionTiles.count(std::pair<int, int>(x, bottomTile)) > 0) {
                        if (playerBottomRect.getGlobalBounds().intersects(collisionTiles.at(std::pair<int, int>(x, bottomTile))->tileBounds.getGlobalBounds())) {
                            SetY(collisionTiles.at(std::pair<int, int>(x, bottomTile))->top - PLAYER_HEIGHT + 2);
                            collisionBot = true;
                            //std::cout << "COLLISION BOT" << std::endl;
                        }
                    }
                }
                if (collisionTiles.count(std::pair<int, int>(x, topTile)) > 0) {
                    if (playerTopRect.getGlobalBounds().intersects(collisionTiles.at(std::pair<int, int>(x, topTile))->tileBounds.getGlobalBounds())) {
                        if (!playerLeftRect.getGlobalBounds().intersects(collisionTiles.at(std::pair<int, int>(x, topTile))->tileBounds.getGlobalBounds()) &&
                            !playerRightRect.getGlobalBounds().intersects(collisionTiles.at(std::pair<int, int>(x, topTile))->tileBounds.getGlobalBounds())){
                            if(!collisionBot){
                                collisionTop = true;
                                SetY(collisionTiles.at(std::pair<int, int>(x, topTile))->bottom);
                                //std::cout << "COLLISION TOP" << std::endl;
                            }
                        }
                    }
                }
            }
            for (int y = topTile; y <= bottomTile; ++y) {
                if (collisionTiles.count(std::pair<int, int>(leftTile, y)) > 0) {
                    if (playerLeftRect.getGlobalBounds().intersects(collisionTiles.at(std::pair<int, int>(leftTile, y))->tileBounds.getGlobalBounds())) {
                        collisionLeft = true;
                        SetX((collisionTiles.at(std::pair<int, int>(leftTile, y))->right-3));
                        xSpeed = 0;
                        //std::cout << "COLLISION LEFT" << std::endl;
                    }
                }
                if (collisionTiles.count(std::pair<int, int>(rightTile, y)) > 0) {
                    if (playerRightRect.getGlobalBounds().intersects(collisionTiles.at(std::pair<int, int>(rightTile, y))->tileBounds.getGlobalBounds())) {
                        collisionRight = true;
                        SetX((collisionTiles.at(std::pair<int, int>(rightTile, y))->left) - PLAYER_WIDTH+3);
                        xSpeed = 0;
                        //std::cout << "COLLISION RIGHT" << std::endl;
                    }
                }
            }
        }

        void CheckJumpCollision(std::map<int,PlayerObject*> &allPlayers){

            //Collision between the players
            for (auto player : allPlayers){
                if (player.second == this) continue;

                if(player.second->playerBottomRect.getGlobalBounds().intersects(playerTopRect.getGlobalBounds())){
                    if(playerState != PlayerStates::invincible && !player.second->killed) {
                        Killed();
                        player.second->JumpKill();
                        player.second->score++;
                    }
                }
                if(player.second->playerLeftRect.getGlobalBounds().intersects(playerRightRect.getGlobalBounds()) ||
                   player.second->playerTopRect.getGlobalBounds().intersects(playerRightRect.getGlobalBounds())){
                    SetX(player.second->GetX()-PLAYER_WIDTH+10);
                }
                if(player.second->playerRightRect.getGlobalBounds().intersects(playerLeftRect.getGlobalBounds()) ||
                   player.second->playerTopRect.getGlobalBounds().intersects(playerLeftRect.getGlobalBounds())){
                    SetX(player.second->GetX()+PLAYER_WIDTH-10);
                }
            }
        }

        void MeleeAttack(std::map<int, PlayerObject *> &allPlayers){ //kjøres under attack

            AnimationMeleeAttack();
            for(auto player : allPlayers){
                if (player.second == this) continue;
                if(player.second->y>=y && player.second->y<y+PLAYER_HEIGHT) { //sjekker om player er på samme X linje
                    if (player.second->x >= x - PLAYER_WIDTH && !isFlipped && player.second->x<x-1){
                        player.second->Killed();
                        score++;
                    }
                    if(player.second->x >= x + PLAYER_WIDTH && isFlipped && player.second->x<x+PLAYER_WIDTH*2){ //sjekker om player er innenfor 1 rute avstand på begge sider
                        player.second->Killed();
                        score++;
                    }
                }
            }
        }

        void PowerUpTick(){//Tick the powerup so that it wont last forever
            if(playerState != PlayerStates::normal){
                if(clockPowerUp.getElapsedTime().asSeconds() >= powerDuration){
                    playerState = PlayerStates::normal;

                }
            }
        }

        bool CheckPowerUpCollision(powerUp &currentPower){

            if (sprite.getGlobalBounds().intersects(currentPower.GetSprite().getGlobalBounds())){ //Check if player colides with a powerup

                if(currentPower.GetType() == PowerType::gun){ SetPowerGun(); }
                if(currentPower.GetType() == PowerType::invincible){ SetPowerInvincible(); }
                if(currentPower.GetType() == PowerType::melee){ SetPowerMelee(); }
                return true;
            }
            else return false;
        }

        void SetPowerGun(){ //Player gets gun powerup
            playerState = PlayerStates::gun;
            clockPowerUp.restart();
            powerDuration = 100;
            ammo = new Ammo(x, y);
            powerUpSprite.setTextureRect(sf::IntRect(TILE_SIZE*5, 0, TILE_SIZE, TILE_SIZE));

        }
        void SetPowerInvincible(){ //Player becomes invinceble
            playerState = PlayerStates::invincible;
            clockPowerUp.restart();
            powerDuration = 10;
        }
        void SetPowerMelee(){ //player can hit
            playerState = PlayerStates::melee;
            clockPowerUp.restart();
            powerDuration = 10;
            powerUpSprite.setTextureRect(sf::IntRect(TILE_SIZE*4, 0, TILE_SIZE, TILE_SIZE));
        }

        void CheckAttack(std::map<int, PlayerObject *> &allPlayers, GameDataRef &data){ //Can player attack?
            if(GetState() == PlayerStates::gun) {
                if(!bulletInAir) { Shoot(data); }
            }
            if(GetState() == PlayerStates::melee) {
                MeleeAttack(allPlayers);
            }
        }

        void Shoot(GameDataRef &data){ //Player shoots
            if(clockFireRate.getElapsedTime().asSeconds() > fireRateTime) {
                bullet = new Bullet(x, y, isFlipped, data); //New bullet object is created
                bulletInAir = true;
                ammo->UseAmmo();
                if (ammo->OutOfAmmo()) playerState = PlayerStates::normal;
                clockFireRate.restart();
            }
        }

        sf::Sprite DrawBullet(){ //draw bullet
            bullet->Move();
            return bullet->GetSprite();
        }

        void BulletTick(std::map<std::pair<int, int>, Tile*> &collisionTiles, std::map<int, PlayerObject *> &allPlayers){

            //if the bullet collide with collisonTiles
            for(auto tile: collisionTiles){
                if(bullet->GetSprite().getGlobalBounds().intersects(tile.second->tileBounds.getGlobalBounds())){
                    BulletKill();
                    return;
                }
            }
            //if the bullet collides with a player
            for(auto player : allPlayers){
                if(bullet->GetSprite().getGlobalBounds().intersects(player.second->sprite.getGlobalBounds())) {
                    if (player.second == this) continue;
                    BulletKill();
                    player.second->Killed();
                    score++;
                    return;

                }
            }
            //if the bullet goes out of the window
            if(!bullet->IsWithingWindow()) BulletKill();

        }

        void BulletKill(){ //bullet eather hits something or is out of the map and gets killed
            bulletInAir = false;
            bullet = nullptr;
        }

        void CheckInvincibleCollision(std::map<int, PlayerObject *> &allPlayers){ //If player is invinceble, kill anyone he collides with
            for(auto player : allPlayers){
                if(player.second->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())){
                    if (player.second == this) continue;
                    player.second->Killed();
                    score++;
                }
            }
        }

        void PowerUpBlink(){
            if(!tileSetChange){
                sprite.setTexture(*goldenTileSet);
                tileSetChange = true;
                clockBlink.restart();
            }
            else if (tileSetChange) {
                sprite.setTexture(*playerTileSet);
                tileSetChange = false;
                clockBlink.restart();
            }
        }

        bool IsBulletInAir(){ return bulletInAir; }
        std::list<ammoRect*> GetTotalAmmo(){ return ammo->GetTotalAmmo(); }
        void AmmoTick(){ ammo->SetRects(x, y); }

        sf::Sprite DrawPowerIcon(){
            if(playerState == PlayerStates::gun){
                powerUpSprite.setPosition(x-TILE_SIZE+32, y);
            }
            else powerUpSprite.setPosition(x-TILE_SIZE+16, y);
            return powerUpSprite;
        }

        void Killed(){ //PlayerObject(this) gets killed
            killed = true;
            KillAnimation();
            playerState = PlayerStates::normal;

            this->x =  -200*(id+1);
            this->y =  -200*(id+1);

            killedClock.restart(); //Restart deathtimer
        }

        int GetRandomNumber(int min, int max){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine generator(seed);
            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(generator);
        }

    protected:
        bool killed = false;
        int timeDead;
        sf::Clock killedClock;
        int score=0;
        int id;
        ///Ai related
        bool jumping;
        bool AI;
        bool jumpingRight = false;
        bool jumpingLeft = false;
        bool attacking = false;
        ///

        int x, y;
        int xSpeed, ySpeed;
        int playerWidth;
        int playerHeight;
        PlayerStates playerState;

        sf::Texture *texture;
        sf::Sprite sprite;
        sf::Sprite powerUpSprite;
        sf::Texture *playerTileSet;
        sf::Texture *goldenTileSet;
        sf::Texture *powerUpTileSet;
        bool tileSetChange;
        sf::Clock clockBlink;
        float blinkTime = 0.15;

        bool collisionBot;
        bool collisionTop;
        bool collisionLeft;
        bool collisionRight;

        sf::RectangleShape playerLeftRect;
        sf::RectangleShape playerRightRect;
        sf::RectangleShape playerTopRect;
        sf::RectangleShape playerBottomRect;

        ///Animation variables
        int frame = 0;
        int frameCount = 4;
        int frameDuration = 100;
        sf::Clock clock;
        int tileX, tileY;
        bool isFlipped = true;
        int animationID = 0;
        int xOld, yOld; // Remembers the x and y posistion from the last frame

        int spriteOffSet = 0;
        ///

        ///Powerups clock
        sf::Clock clockPowerUp;
        int powerDuration;

        Bullet *bullet;
        bool bulletInAir;
        sf::Clock clockFireRate;
        float fireRateTime = 0.5;

        Ammo *ammo;
    };
}

#endif //KJELEDYR_PLAYEROBJECT_H
