#pragma once
#include "Physics.h"

//forward declaration for player pointer
class Player;
class LevelScreen;

class Grenade :
    public Physics
{
public:

    Grenade(sf::Vector2f newPos, Player* newPlayerPtr, LevelScreen* newLevelPtr, sf::Vector2f newInitialVel);

    void Update(sf::Time frameTime) override;

    void Draw(sf::RenderTarget& target);

    void UpdateGrenadeAcceleration() override;

    void HandleCollision(SpriteObject& other) override;

    void DamageCheck(Player& _player);

 

private:

    bool isDetonating;
    sf::Time boomTimer;
    sf::Clock boomClock;
    Player* playerPtr;
    LevelScreen* levelPtr;
    sf::FloatRect blastRadius;
    sf::Vector2f aimDirection;
    
    

};

