#include "pch.h"

namespace Utils 
{

sf::Vector2f Vector2Normalize(const sf::Vector2f& vector)
{
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    if (magnitude == 0) {
        return { 0, 0 };
    }

    sf::Vector2f normalized = { vector.x / magnitude, vector.y / magnitude };

    return normalized;
}

float GetDeltaTime()
{
    return 0.016f;
}

float GetDistance(sf::Vector2f Start, sf::Vector2f End)
{
    float tempX = pow(End.x - Start.x, 2);
    float tempY = pow(End.y - Start.y, 2);

    float dst = sqrt(tempX + tempY);

    return dst;
}

sf::Vector2f GetVector(sf::Vector2f Start, sf::Vector2f End)
{
	sf::Vector2f temp = { End.x - Start.x, End.y - Start.y };

	return temp;
}

}
