#include "Floor.h"
#include "AssetManager.h"

Floor::Floor(sf::Vector2f newPos)
	:SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/floor.png"));
	collisionType = CollisionType::AABB;
}
