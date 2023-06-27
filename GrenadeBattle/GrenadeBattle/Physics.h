#pragma once
#include "SpriteObject.h"
class Physics :
    public SpriteObject
{
public:
    Physics(bool newDragOn);

    virtual void Update(sf::Time frameTime) override;

    virtual void Draw(sf::RenderTarget& target) override;

    virtual void UpdateAcceleration();

    

    

protected:
    sf::Vector2f velocity;
    sf::Vector2f twoFramesOldPos;
    sf::Vector2f acceleration;
    bool dragOn;

    


    

    

};

