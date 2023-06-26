#include "Grenade.h"
#include "Player.h"
#include "LevelScreen.h"

Grenade::Grenade(sf::Vector2f newPos, Player* newPlayerPtr, LevelScreen* newLevelPtr, sf::Vector2f newInitialVel)
	:Physics()
	, levelPtr(newLevelPtr)
	, isDetonating(false)
	, playerPtr(newPlayerPtr)
	, blastRadius()
	
	
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/grenade.png"));
	SetPosition(newPos);
	boomClock.restart();
	boomTimer = boomClock.getElapsedTime();

	blastRadius.width = 50;
	blastRadius.height = 30;
	aimDirection = newInitialVel;
	velocity = velocity + aimDirection;
	
}

void Grenade::Update(sf::Time frameTime)
{
	blastRadius.left = GetPosition().x;
	blastRadius.top = GetPosition().y;
	Physics::Update(frameTime);
	
	//UpdateGrenadeAcceleration(); //todo ask sarah if i need to remove call of this function from physics update or here

	if (boomTimer > sf::seconds(1.5f))
	{
		isDetonating = true;
		
	}
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
			playerPtr = &_player;
			playerPtr->ChangeLives(1);
			levelPtr->ResetPlay();
		}
		else
		{
			if (blastTimer > sf::seconds(1.0f))
			{
				isDetonating = false;
				alive = false;
			}
		}
	}
}


