#pragma once

#include <SFML/System/Vector2.hpp>

namespace Utils
{
	sf::Vector2f Vector2Normalize(const sf::Vector2f& vector);
	float Vector2Magnitude(const sf::Vector2f& vector);
	std::string getRandomName(bool getDuplicates = false);
}