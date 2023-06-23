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


};

