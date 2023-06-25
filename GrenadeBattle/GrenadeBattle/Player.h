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
    void HandleCollision(SpriteObject& other) override;

    void SetHasAttacked(bool newHasAttacked);
    void AttackCooldown();
    void LaunchGrenade();

    void ChangeLives(int minusLife);
    void SetLives(int newLives);

    void UpdateAim();
    

    sf::Vector2f GetAim();

    int GetPlayerIndex();

    void CheckLives();

protected:
    int lives;
    bool hasAttacked;

    

private:
    sf::Time attackCooldownTimer;
    sf::Clock attackCooldownClock;
    LevelScreen* levelScreenPtr;
    sf::Vector2f aim;
    int playerIndex;
    sf::Sprite launcher;

    

    

};

