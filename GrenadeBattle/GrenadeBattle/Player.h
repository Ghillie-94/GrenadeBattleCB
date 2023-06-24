#pragma once
#include "Physics.h"

//forward declaration for level screen pointer 
class LevelScreen;

class Player :
    public Physics
{
public:

    Player(LevelScreen* newLevelScreenPtr);

    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

    void SetCanAttack(bool newCanAttack);
    void AttackCooldown();
    void LaunchGrenade();

    void SetLives(int minusLife);

protected:
    int lives;
    bool hasAttacked;
    bool hasJumped;

private:
    sf::Time attackCooldownTimer;
    sf::Clock attackCooldownClock;

    sf::Time jumpCooldownTimer;
    sf::Clock jumpCooldownClock;

};

