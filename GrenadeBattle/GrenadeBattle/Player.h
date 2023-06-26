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
    void Draw(sf::RenderTarget& target) override;
    void UpdatePlayerAcceleration() override;
    void HandleCollision(SpriteObject& other) override;
    void UpdatePips();

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

    sf::Vector2f ProjectilePrediction(float newTime, sf::Vector2f newIV, sf::Vector2f newIP, sf::Vector2f gravity);

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

    sf::Sprite pip;
    std::vector<sf::Sprite*> pips;
    

    

};

