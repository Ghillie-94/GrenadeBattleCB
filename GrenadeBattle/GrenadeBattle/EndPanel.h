#pragma once
#include <SFML/Graphics.hpp>


class EndPanel
{
public:
	EndPanel(sf::RenderWindow* newWindow);

	void Update(sf::Time frameTime);
	void Draw(sf::RenderTarget& target);

	void SetPosition(sf::Vector2f newPos);

	void StartAnimation();
	void ResetPosition();

	void SetWinner(std::string newWinner);

	std::string GetWinner();

protected:
	std::string winner;

private:

	sf::Sprite background;
	sf::Text title;
	sf::Text message;
	sf::Vector2f position;
	sf::RenderWindow* window;
	bool animatingIn;
	sf::Clock animationClock;
	
};

