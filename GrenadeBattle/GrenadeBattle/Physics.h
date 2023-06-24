#pragma once
#include "SpriteObject.h"
class Physics :
    public SpriteObject
{
public:
    Physics();

    virtual void Update(sf::Time frameTime) override;

    void UpdatePlayerAcceleration();

    void UpdateGrenadeAcceleration();

protected:
    sf::Vector2f velocity;
    sf::Vector2f twoFramesOldPos;
    sf::Vector2f acceleration;

};

