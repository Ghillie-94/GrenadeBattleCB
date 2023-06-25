#include "Player.h"
#include "LevelScreen.h"
#include "VectorHelper.h"
#include <iostream>

Player::Player(LevelScreen* newLevelScreenPtr, int newPlayerIndex)
	:Physics()
	, lives()
	, hasAttacked(false)
	, hasJumped(false)
	, attackCooldownTimer()
	, attackCooldownClock()
	, levelScreenPtr(newLevelScreenPtr)
	, aim(GetPosition())
	, playerIndex(newPlayerIndex)
	, launcher()
{
	
	
	
	SetSprite();
	launcher.setTexture(AssetManager::RequestTexture("Assets/Graphics/launcher.png"));
	launcher.setPosition(GetAim());

	collisionType = CollisionType::AABB;
	
}

void Player::Update(sf::Time frameTime)
{
	UpdateAim();
	GetAim();
	LaunchGrenade();
	AttackCooldown();
	Physics::Update(frameTime);
	launcher.setPosition(GetPosition());
	JumpCooldown();
}

void Player::UpdatePlayerAcceleration()
{
	const float GRAVITY = 500;
	const float PLAYERACCEL = 1500;
	const float JUMPSPEED = 2500;

	//update acceleration
	acceleration.x = 0;
	acceleration.y = GRAVITY;

	//Player1 movement & jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playerIndex == 1)
	{
		acceleration.x = -PLAYERACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerIndex == 1)
	{
		acceleration.x = PLAYERACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && playerIndex == 1)
	{
		if (!hasJumped)
		{
			acceleration.y = -JUMPSPEED;
			SetHasJumped(true);
			jumpCooldownClock.restart();
			JumpCooldown();
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerIndex == 2)
	{
		acceleration.x = -PLAYERACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerIndex == 2)
	{
		acceleration.x = PLAYERACCEL;
	}
}

void Player::HandleCollision(SpriteObject& other)
{
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPos = GetPosition();

	if (abs(depth.x) < abs(depth.y))
	{
		// Move in X direction
		newPos.x += depth.x;
		velocity.x = 0;
		acceleration.x = 0;
	}
	else
	{
		// Move in y direction
		newPos.y += depth.y;
		velocity.y = 0;
		acceleration.y = 0;

		// If we collided from above
		if (depth.y < 0)
		{
			velocity.y = 0;
			acceleration.y = 0;
		}
	}

	SetPosition(newPos);
}

void Player::SetHasAttacked(bool newCanAttack)
{
	hasAttacked = newCanAttack;
}

void Player::AttackCooldown()
{
	if (hasAttacked)
	{
		attackCooldownTimer = attackCooldownClock.getElapsedTime();
		if (attackCooldownTimer > sf::seconds(1.5f))
		{
			SetHasAttacked(false);
		}
	}
}

void Player::LaunchGrenade()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && playerIndex == 1)
	{
		if (!hasAttacked)
		{
			std::cout << "player1 attempted to launch a grenade" << std::endl;
			levelScreenPtr->AddGrenade("player1");
			SetHasAttacked(true);
			attackCooldownClock.restart();
			AttackCooldown();
		}
		

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		if (!hasAttacked)
		{
			std::cout << "player2 attempted to launch a grenade" << std::endl;
			levelScreenPtr->AddGrenade("player2");
			SetHasAttacked(true);
			attackCooldownClock.restart();
			AttackCooldown();
		}
	}
}

void Player::ChangeLives(int minusLife)
{
	lives = -minusLife;
}

void Player::SetLives(int newLives)
{
	lives = newLives;
}

void Player::UpdateAim()
{
	sf::Vector2f direction = (aim - GetPosition());
	direction = VectorHelper::Normalise(direction);
	float angle = atan(direction.y / direction.x);

	//player one input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playerIndex == 1)
	{
		angle = +10;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playerIndex == 1)
	{
		angle = -10;
	}

	//player two input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerIndex == 2)
	{
		angle = +10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && playerIndex == 2)
	{
		angle = -10;
	}
	aim.x = cos(angle);
	aim.y = sin(angle);
	launcher.rotate(angle);
}



sf::Vector2f Player::GetAim()
{
	return aim;
}

int Player::GetPlayerIndex()
{
	return playerIndex;
}

void Player::CheckLives()
{
	if (lives <= 0)
	{
		if (playerIndex == 1)
		{
			levelScreenPtr->TriggerEndState(true, "player1");
		}
		if (playerIndex == 2)
		{
			levelScreenPtr->TriggerEndState(true, "player2");
		}
		
	}
}

void Player::SetSprite()
{
	if (playerIndex == 2)
	{
		aim.x = aim.x - 20;
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/player_2.png"));
		
	}
	if (playerIndex == 1)
	{
		aim.x = aim.x + 20;
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/player_1.png"));
		
	}
}

void Player::JumpCooldown()
{
	if (hasJumped)
	{
		jumpCooldownTimer = jumpCooldownClock.getElapsedTime();
		if (jumpCooldownTimer > sf::seconds(1.5f))
		{
			SetHasJumped(false);
		}
	}
}

void Player::SetHasJumped(bool newHasJumped)
{
	hasJumped = newHasJumped;
}
