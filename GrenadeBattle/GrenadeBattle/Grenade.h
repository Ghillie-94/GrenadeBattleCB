#pragma once
#include "Physics.h"

//forward declaration for player pointer
class Player;

class Grenade :
    public Physics
{
public:

    Grenade(Player* newPlayerPtr);

    void Update(sf::Time frameTime) override;

    void HandleCollision(SpriteObject& other) override;

    void DamageCheck(Player& _player);

private:

    bool isDetonating;
    sf::Time boomTimer;
    sf::Clock boomClock;
    Player* playerPtr;

};

