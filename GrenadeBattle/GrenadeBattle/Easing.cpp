#include "Easing.h"

sf::Vector2f Easing::Linear(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
	return (change / duration) * time + begin;
}

sf::Vector2f Easing::EaseInQuad(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
	return (change / (duration * duration)) * time * time + begin;
}

sf::Vector2f Easing::EaseOutQuad(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
	return ((-change * time) / (duration * duration) + 2.0f * ((change * time) / duration) + begin);
}
