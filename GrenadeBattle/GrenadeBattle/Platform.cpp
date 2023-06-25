#include "Platform.h"
#include "AssetManager.h"

Platform::Platform(sf::Vector2f newPos)
	:SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/tile.png"));
	SetPosition(newPos);
}
