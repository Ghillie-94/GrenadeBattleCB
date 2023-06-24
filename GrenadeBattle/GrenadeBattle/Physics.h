#pragma once
#include "SpriteObject.h"
class Physics :
    public SpriteObject
{
public:
    Physics();

    virtual void Update(sf::Time frameTime) override;

    void UpdatePlayerAcceleration();

    virtual void UpdateGrenadeAcceleration();

    void JumpCooldown();

protected:
    sf::Vector2f velocity;
    sf::Vector2f twoFramesOldPos;
    sf::Vector2f acceleration;

    bool hasPlayerJumped;

private:
    sf::Time jumpCooldownTimer;
    sf::Clock jumpCooldownClock;

    

};

