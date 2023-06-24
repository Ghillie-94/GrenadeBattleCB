#include "Player.h"
#include "LevelScreen.h"
#include "VectorHelper.h"
#include <iostream>

Player::Player(LevelScreen* newLevelScreenPtr, int newPlayerIndex)
	:Physics()
	,lives()
	,hasAttacked(false)
	,attackCooldownTimer()
	,attackCooldownClock()
	,levelScreenPtr(newLevelScreenPtr)
	,aim(GetPosition())
	,playerIndex(newPlayerIndex)
{
	aim.x = aim.x - 20;
	
}

void Player::Update(sf::Time frameTime)
{
	UpdateAim();
	LaunchGrenade();
	AttackCooldown();
	GetAim();
}

void Player::HandleCollision(SpriteObject& other)
{
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		std::cout << "player1 attempted to launch a grenade" << std::endl;
		levelScreenPtr->AddGrenade("player1");

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		std::cout << "player2 attempted to launch a grenade" << std::endl;
		levelScreenPtr->AddGrenade("player2");
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
