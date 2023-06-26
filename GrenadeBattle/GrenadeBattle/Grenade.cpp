#include "Grenade.h"
#include "Player.h"
#include "LevelScreen.h"

Grenade::Grenade(sf::Vector2f newPos, Player* newPlayerPtr, LevelScreen* newLevelPtr)
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
}

void Grenade::Update(sf::Time frameTime)
{
	blastRadius.left = GetPosition().x;
	blastRadius.top = GetPosition().y;
	Physics::Update(frameTime);
	aimDirection = playerPtr->GetAim(); //move to constructor??
	//UpdateGrenadeAcceleration(); //todo ask sarah if i need to remove call of this function from physics update or here

	if (boomTimer > sf::seconds(1.5f))
	{
		isDetonating = true;
		
	}
}

void Grenade::UpdateGrenadeAcceleration()
{
	int index = playerPtr->GetPlayerIndex();
	const float GRENADEACCEL = 2500;
	const float GRAVITY = 500;
	

	if (index == 1)
	{
		
		//update acceleration
		acceleration.x = GRENADEACCEL; //todo add aim vector
		acceleration.y = GRAVITY;
	}
	if (index == 2)
	{
		
		//update acceleration
		acceleration.x = -GRENADEACCEL; //todo add aim vector
		acceleration.y = GRAVITY;
	}
	
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


