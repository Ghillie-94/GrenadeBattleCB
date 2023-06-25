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
	//UpdateGrenadeAcceleration(); //todo ask sarah if i need to remove call of this function from physics update or here

	if (boomTimer > sf::seconds(1.5f))
	{
		isDetonating = true;
		
	}
}

void Grenade::UpdateGrenadeAcceleration()
{
	int index = playerPtr->GetPlayerIndex();
	const float GRENADEACCEL = 5000;
	const float GRAVITY = 500;
	

	if (index == 1)
	{
		sf::Vector2f aimDirection = playerPtr->GetAim();
		//update acceleration
		acceleration.x = GRENADEACCEL * aimDirection.x; //todo add aim vector
		acceleration.y = GRAVITY * aimDirection.y;
	}
	if (index == 2)
	{
		sf::Vector2f aimDirection = playerPtr->GetAim();
		//update acceleration
		acceleration.x = -GRENADEACCEL * aimDirection.x; //todo add aim vector
		acceleration.y = GRAVITY * aimDirection.y;
	}
	
}

void Grenade::HandleCollision(SpriteObject& other)
{
}

void Grenade::DamageCheck(Player& _player)
{
	if (isDetonating)
	{
		if (blastRadius.intersects(_player.GetAABB()))
		{
			playerPtr = &_player;
			playerPtr->ChangeLives(1);
			levelPtr->ResetPlay();
		}
	}
}


