#pragma once
#include "Physics.h"

//forward declaration for level screen pointer 
class LevelScreen;

class Player :
    public Physics
{
public:

    Player(LevelScreen* newLevelScreenPtr, int newPlayerIndex);

    void Update(sf::Time frameTime) override;
    void UpdatePlayerAcceleration() override;
    void HandleCollision(SpriteObject& other) override;

    void SetHasAttacked(bool newHasAttacked);
    void AttackCooldown();
    void LaunchGrenade();

    void ChangeLives(int minusLife);
    void SetLives(int newLives);

    void UpdateAim();
    

    sf::Vector2f GetInitialLaunchVelocity();

    int GetPlayerIndex();

    void CheckLives();
    void SetSprite();
    void JumpCooldown();
    void SetHasJumped(bool newHasJumped);

protected:
    int lives;
    bool hasAttacked;
    bool hasJumped;
    bool isAirTime;
    

private:
    sf::Time attackCooldownTimer;
    sf::Clock attackCooldownClock;
    LevelScreen* levelScreenPtr;
    sf::Vector2f aim;
    int playerIndex;
    sf::Sprite launcher;
    sf::Time jumpCooldownTimer;
    sf::Clock jumpCooldownClock;
    sf::Time airTime;
    sf::Vector2f initialLaunchVelocity;
    const float LAUNCHSPEED;
    

    

};

