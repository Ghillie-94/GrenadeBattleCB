#pragma once
#include <SFML/Graphics.hpp>

//forward declaration of game class for gamePtr parameter pass into constructor
class Game;

class Screen
{
public:

	Screen(Game* newGamePtr);

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

protected:

	Game* gamePtr;


};

