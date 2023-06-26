#include "Player.h"
#include "LevelScreen.h"
#include "VectorHelper.h"
#include <iostream>

Player::Player(LevelScreen* newLevelScreenPtr, int newPlayerIndex)
	:Physics(true)
	, lives()
	, hasAttacked(false)
	, hasJumped(false)
	, attackCooldownTimer()
	, attackCooldownClock()
	, levelScreenPtr(newLevelScreenPtr)
	, aim(GetPosition())
	, playerIndex(newPlayerIndex)
	, launcher()
	, LAUNCHSPEED(1000)
	, pip()
	, pips()
{
	
	
	
	SetSprite();
	launcher.setTexture(AssetManager::RequestTexture("Assets/Graphics/launcher.png"));
	launcher.setPosition(GetPosition());

	collisionType = CollisionType::AABB;
	pip.setTexture(AssetManager::RequestTexture("Assets/Graphics/pip.png"));
	pips.push_back(new sf::Sprite(pip)); /*1*/ pips.push_back(new sf::Sprite(pip)); /*2*/ pips.push_back(new sf::Sprite(pip)); /*3*/ pips.push_back(new sf::Sprite(pip)); /*4*/ pips.push_back(new sf::Sprite(pip)); /*5*/ pips.push_back(new sf::Sprite(pip)); /*6*/ pips.push_back(new sf::Sprite(pip)); /*7*/ pips.push_back(new sf::Sprite(pip)); /*8*/ pips.push_back(new sf::Sprite(pip)); /*9*/ pips.push_back(new sf::Sprite(pip)); /*10*/
	
}

void Player::Update(sf::Time frameTime)
{
	UpdateAim();
	LaunchGrenade();
	AttackCooldown();
	Physics::Update(frameTime);
	launcher.setPosition(GetPosition());
	JumpCooldown();
	UpdatePips();
}

void Player::Draw(sf::RenderTarget& target)
{
	SpriteObject::Draw(target);
	
	for (int i = 0; i < pips.size(); ++i)
	{
		target.draw(*pips[i]);
	}
}

void Player::UpdatePlayerAcceleration()
{
	const float GRAVITY = 500;
	const float PLAYERACCEL = 15;
	const float JUMPSPEED = 1000;

	//update acceleration
	acceleration.x = 0;
	acceleration.y = GRAVITY;

	//Player1 movement & jump
	if (playerIndex == 1)
	{
		float leftJoystickInput = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
		acceleration.x = PLAYERACCEL * leftJoystickInput;

		if (sf::Joystick::isButtonPressed(0, 0) == true)
		{
			if (!hasJumped)
			{
				acceleration.y = -JUMPSPEED;
				//SetHasJumped(true); //add airtime
				jumpCooldownClock.restart();
				isAirTime = true;
				JumpCooldown();
			}
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && playerIndex == 2)
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
		acceleration.x = -PLAYERACCEL*100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerIndex == 2)
	{
		acceleration.x = PLAYERACCEL*100;
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

void Player::UpdatePips()
{
	float timeStep = 0;
	sf::Vector2f iV;
	sf::Vector2f iP;
	sf::Vector2f g;
	iV = GetInitialLaunchVelocity();
	iP = GetPosition();
	g.y = 1000;
	sf::Vector2f newPipPos;
	for (int i = 0; i < pips.size(); ++i)
	{
		timeStep += 0.1f;
		newPipPos = ProjectilePrediction(timeStep, iV, iP, g);
		pips[i]->setPosition(newPipPos);
		
	}

	
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
	float axisValue;
	if (playerIndex == 1)
	{
		axisValue = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z);
		if (axisValue < -90)
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
	

	//player one input
	if (playerIndex == 1)
	{
		//according to SFML forums joystick axes are mapped depending on the gamepad's driver
		//it should be U and R for the right stick on a xbox 360 pad
		aim.x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U);
		aim.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V);

		aim = VectorHelper::Normalise(aim);
		initialLaunchVelocity = aim * LAUNCHSPEED;
		
	}
}



sf::Vector2f Player::GetInitialLaunchVelocity()
{
	return initialLaunchVelocity;
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
	if (isAirTime)
	{
		airTime = jumpCooldownClock.getElapsedTime();
		

		if (airTime > sf::seconds(1))
		{
			isAirTime = false;
			SetHasJumped(true);
		}
		
		
	}
	
	
	jumpCooldownClock.restart();
	jumpCooldownTimer = jumpCooldownClock.getElapsedTime();
	if (jumpCooldownTimer > sf::seconds(1.5f))
	{
		SetHasJumped(false);
	}
}

void Player::SetHasJumped(bool newHasJumped)
{
	hasJumped = newHasJumped;
}

sf::Vector2f Player::ProjectilePrediction(float newTime, sf::Vector2f newIV, sf::Vector2f newIP, sf::Vector2f gravity)
{
	
	return gravity* (0.5f * newTime * newTime) + (newIV * newTime) + newIP;

}
