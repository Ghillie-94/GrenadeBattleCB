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
}

void EndPanel::Update(sf::Time frameTime)
{
}

void EndPanel::Draw(sf::RenderTarget& target)
{
}

void EndPanel::SetPosition(sf::Vector2f newPos)
{
}

void EndPanel::StartAnimation()
{
}

void EndPanel::ResetPosition()
{
}

void EndPanel::SetWinner(std::string newWinner)
{
}
