#pragma once
#include <SFML/System.hpp>

namespace VectorHelper
{
	float SquareMagnitude(sf::Vector2f vec);
	float Magnitude(sf::Vector2f vec);

	sf::Vector2f Normalise(sf::Vector2f vec);
	float DotProduct(float vec1X, float vec1Y, float vec2X, float vec2Y);
	sf::Vector3f CrossProduct3D(float vec1X, float vec1Y, float vec1Z, float vec2X, float vec2Y, float vec2Z);

	sf::Vector2f Reflect(sf::Vector2f incoming, sf::Vector2f normal);


};

