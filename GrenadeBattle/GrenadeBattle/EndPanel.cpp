#include "EndPanel.h"
#include "AssetManager.h"
#include "Easing.h"

EndPanel::EndPanel(sf::RenderWindow* newWindow)
	:background()
	, title()
	, message()
	, position(0, 0)
	, window(newWindow)
	, animatingIn(false)
	, animationClock()
{
	background.setTexture(AssetManager::RequestTexture("insertgraphicforpanelhere"));
	background.setScale(5.0f, 5.0f);

	title.setFont(AssetManager::RequestFont("Assets/Fonts/dogica.ttf"));
	title.setCharacterSize(70);
	title.setFillColor(sf::Color::White);
	

	message.setFont(AssetManager::RequestFont("Assets/Fonts/dogica.ttf"));
	message.setCharacterSize(30);
	message.setString("Restart");
	message.setFillColor(sf::Color::White);
	

	ResetPosition();
}

void EndPanel::Update(sf::Time frameTime)
{
	title.setString(GetWinner());
	if (animatingIn)
	{
		float xPos = window->getSize().x * 0.5f - background.getGlobalBounds().width * 0.5f;
		float yPos = window->getSize().y;
		float finalYPos = window->getSize().y * 0.5f - background.getGlobalBounds().height * 0.5f;

		sf::Vector2f begin(xPos, yPos);
		sf::Vector2f change(0, finalYPos - yPos);
		float duration = 1.0f;
		float time = animationClock.getElapsedTime().asSeconds();

		sf::Vector2f newPosition = Easing::EaseInQuad(begin, change, duration, time);
		SetPosition(newPosition);

		if (time >= duration)
		{
			SetPosition(begin + change);
			animatingIn = false;
		}
	}
}

void EndPanel::Draw(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(message);
	target.draw(title);
}

void EndPanel::SetPosition(sf::Vector2f newPos)
{
	background.setPosition(newPos);

	// center the title on the x direction
	float titleX = background.getGlobalBounds().width * 0.5f - title.getGlobalBounds().width * 0.5f;
	title.setPosition(sf::Vector2f(newPos.x + titleX, newPos.y + 50));

	// center the message in the x and y direction
	float messageX = background.getGlobalBounds().width * 0.5f - message.getGlobalBounds().width * 0.5f;
	float messageY = background.getGlobalBounds().height * 0.5f - message.getGlobalBounds().height * 0.5f;
	message.setPosition(sf::Vector2f(newPos.x + messageX, newPos.y + messageY));
}

void EndPanel::StartAnimation()
{
	animatingIn = true;
	animationClock.restart();
}

void EndPanel::ResetPosition()
{
	float xPos = window->getSize().x * 0.5f - background.getGlobalBounds().width * 0.5f;
	float yPos = window->getSize().y;
	SetPosition(sf::Vector2f(xPos, yPos));
}

void EndPanel::SetWinner(std::string newWinner)
{
	winner = newWinner;
}

std::string EndPanel::GetWinner()
{
	return winner;
}
