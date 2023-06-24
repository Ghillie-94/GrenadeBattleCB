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

    void ChangeLives(int minusLife);
    void SetLives(int newLives);

protected:
    int lives;
    bool hasAttacked;
    

private:
    sf::Time attackCooldownTimer;
    sf::Clock attackCooldownClock;

    

};

