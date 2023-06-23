#include "SpriteObject.h"

SpriteObject::SpriteObject()
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
}

sf::Vector2f SpriteObject::GetPosition()
{
	return sf::Vector2f();
}

void SpriteObject::SetPosition(sf::Vector2f newPos)
{
}

void SpriteObject::SetPosition(float newX, float newY)
{
}

bool SpriteObject::CheckCollision(SpriteObject& other)
{
	return false;
}

void SpriteObject::SetColliding(bool newColliding)
{
}

sf::Vector2f SpriteObject::GetCollisionDepth(SpriteObject& other)
{
	return sf::Vector2f();
}

void SpriteObject::HandleCollision(SpriteObject& other)
{
}

void SpriteObject::SetAlive(bool newAlive)
{
}

sf::FloatRect SpriteObject::GetAABB()
{
	return sf::FloatRect();
}

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	return sf::Vector2f();
}

float SpriteObject::GetCircleColliderRadius()
{
	return 0.0f;
}
