#include "VectorHelper.h"

float VectorHelper::SquareMagnitude(sf::Vector2f vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

float VectorHelper::Magnitude(sf::Vector2f vec)
{
    return sqrt(SquareMagnitude(vec));
}

sf::Vector2f VectorHelper::Normalise(sf::Vector2f vec)
{
	float mag = Magnitude(vec);

	vec.x = vec.x / mag;
	vec.y = vec.y / mag;


	return vec;
}

//************************************
//Practical Task - Reflection
//************************************

float VectorHelper::DotProduct(float vec1X, float vec1Y, float vec2X, float vec2Y)
{
	return (vec1X * vec2X) + (vec1Y * vec2Y);
}

sf::Vector3f VectorHelper::CrossProduct3D(float vec1X, float vec1Y, float vec1Z, float vec2X, float vec2Y, float vec2Z)
{
	sf::Vector3f crossProduct;
	crossProduct.x = vec1Y * vec2Z - vec1Z * vec2Y;
	crossProduct.y = vec1Z * vec2X - vec1X * vec2Z;
	crossProduct.z = vec1X * vec2Y - vec1Y * vec2X;
	return crossProduct;

}

sf::Vector2f VectorHelper::Reflect(sf::Vector2f incoming, sf::Vector2f normal)
{
	sf::Vector2f reflection;
	
	reflection = incoming - (2.0f * normal) * (DotProduct(incoming.x, incoming.y, normal.x , normal.y));
	return reflection;
}






