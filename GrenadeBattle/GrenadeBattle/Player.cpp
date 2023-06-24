#include "Player.h"

Player::Player(LevelScreen* newLevelScreenPtr)
{
}

void Player::Update(sf::Time frameTime)
{
}

void Player::HandleCollision(SpriteObject& other)
{
}

void Player::SetCanAttack(bool newCanAttack)
{
}

void Player::AttackCooldown()
{
}

void Player::LaunchGrenade()
{
}

void Player::ChangeLives(int minusLife)
{
	lives = -minusLife;
}

void Player::SetLives(int newLives)
{
	lives = newLives;
}
