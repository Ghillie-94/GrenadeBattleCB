#include "Grenade.h"
#include "Player.h"
#include "LevelScreen.h"
#include "VectorHelper.h"
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
	if (!nullptr)
	{
		SpriteObject::Draw(target);
	}
	
}

void Grenade::UpdateAcceleration()
{
	const float GRAVITY = 1000;
	

	//update acceleration 
	acceleration.y = GRAVITY;
	
}

void Grenade::HandleCollision(SpriteObject& other)
{
	//************************************
	//Practical Task - Reflection
	//************************************
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPos = GetPosition();
	sf::Vector2f calcVector;
	sf::Vector2f calcVector2;
	sf::Vector2f planeLine;
	sf::Vector2f reflect;
	
	if (abs(depth.x) < abs(depth.y))
	{
		// Move in x direction
		newPos.x += depth.x * 2.0f;
		calcVector.x = other.GetAABB().left;
		calcVector.y = other.GetAABB().top;
		calcVector2.x = other.GetAABB().left;
		calcVector2.y = other.GetAABB().top + other.GetAABB().height;
		planeLine = calcVector - calcVector2;
		planeLine = VectorHelper::GetNormal(planeLine);
		planeLine = VectorHelper::Normalise(planeLine);
		reflect = VectorHelper::Reflect(velocity, planeLine);
		velocity = reflect;

	}
	else
	{
		// Move in y direction
		newPos.y += depth.y*2.0f;
		
		//acceleration.y = 0;

		// If we collided from above
		if (depth.y < 0)
		{
			calcVector.x = other.GetAABB().left;
			calcVector.y = other.GetAABB().top;
			calcVector2.x = other.GetAABB().left + other.GetAABB().width;
			calcVector2.y = other.GetAABB().top;
			normal = calcVector - calcVector2;
			normal = VectorHelper::GetNormal(normal);
			normal = VectorHelper::Normalise(normal);
			reflect = VectorHelper::Reflect(velocity, normal);
			velocity = reflect;
		}
	}

	SetPosition(newPos);
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
			otherPlayerPtr->SetAlive(false);
			//levelPtr->ResetPlay(); //call this in levelscreen instead if playerPtr->GetAlive() == false
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


