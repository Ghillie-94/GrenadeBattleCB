#include "Grenade.h"
#include "Player.h"
#include "LevelScreen.h"
#include <iostream>

Grenade::Grenade(sf::Vector2f newPos, Player* newPlayerPtr, LevelScreen* newLevelPtr, sf::Vector2f newInitialVel)
	:Physics(false)
	, levelPtr(newLevelPtr)
	, isDetonating(false)
	, playerPtr(newPlayerPtr)
	, otherPlayerPtr(nullptr)
	, blastRadius()
	
	
	
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/grenade.png"));
	SetPosition(newPos);
	boomClock.restart();
	

	blastRadius.width = 120;
	blastRadius.height = 60;
	aimDirection = newInitialVel;
	velocity = velocity + aimDirection;
	
}

void Grenade::Update(sf::Time frameTime)
{
	blastRadius.left = GetPosition().x;
	blastRadius.top = GetPosition().y;
	Physics::Update(frameTime);
	
	boomTimer = boomClock.getElapsedTime();

	if (boomTimer > sf::seconds(1.5f))
	{
		SetDetonation(true);
	}
	
	
}

void Grenade::Draw(sf::RenderTarget& target)
{
	SpriteObject::Draw(target);
}

void Grenade::UpdateGrenadeAcceleration()
{
	const float GRAVITY = 1000;
	

	//update acceleration 
	acceleration.y = GRAVITY;
	
}

void Grenade::HandleCollision(SpriteObject& other)
{
}

void Grenade::DamageCheck(Player& _player)
{
	if (isDetonating)
	{
		sf::Clock blastCooldown;
		sf::Time blastTimer;
		blastCooldown.restart();
		blastTimer = blastCooldown.getElapsedTime();
		if (blastRadius.intersects(_player.GetAABB()))
		{
			otherPlayerPtr = &_player;
			otherPlayerPtr->ChangeLives(1);
			levelPtr->ResetPlay();
		}
		if (blastTimer > sf::seconds(1.0f))
		{
			SetDetonation(false);
			alive = false;
		}
	}
	
}

void Grenade::SetDetonation(bool newDetonation)
{
	isDetonating = newDetonation;
	std::cout << "Grenade Detonated" << std::endl;
}


