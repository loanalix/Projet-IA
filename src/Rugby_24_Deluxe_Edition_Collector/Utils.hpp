#pragma once

#include <SFML/System/Vector2.hpp>

namespace Utils
{
	sf::Vector2f Vector2Normalize(const sf::Vector2f& vector);

	float GetDistance(sf::Vector2f Start, sf::Vector2f End);

	sf::Vector2f GetVector(sf::Vector2f Start, sf::Vector2f End);
}