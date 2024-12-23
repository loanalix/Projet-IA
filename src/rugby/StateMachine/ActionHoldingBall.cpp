#include "pch.h"
#include "ActionHoldingBall.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#define SPEED_DEBUFF 10

void ActionHoldingBall::Start(Player* Player)
{
	if (Player->getTeam() == Context::Team::Green)
	{
		Player->setDirection(Utils::Vector2Normalize(sf::Vector2f(1, 0)));
	}
	else
	{
		Player->setDirection(Utils::Vector2Normalize(sf::Vector2f(-1, 0)));
	}
}

void ActionHoldingBall::Update(Player* player)
{
	player->setSpeed(player->getBaseSpeed() - SPEED_DEBUFF);

	std::vector<Player*> players = GameManager::Get()->getPlayers();
	for (auto p : players) {
		if (p != player && p->getTeam() == player->getTeam()) {
			bool possible = true;

			//angles betwen players
			sf::Vector2f direction = p->getPosition() - player->getPosition();
			float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			sf::RectangleShape line(sf::Vector2f(length, 5.f));


			line.setPosition(player->getPosition());
			line.setRotation(atan2(direction.y, direction.x) * 180.f / 3.14159f);

			// check if enemy in the way
			for (auto e : players) {
				if (e->getTeam() != player->getTeam())
				{
					if (line.getGlobalBounds().intersects(e->getShape().getGlobalBounds()))
					{
						possible = false;
						break;
					}
				}
			}
			if (possible) {
				line.setFillColor(sf::Color::Blue);
			}
			else {
				line.setFillColor(sf::Color::Red);
			}
#ifdef _DEBUG
			GameManager::Get()->getWindow()->draw(line);
#endif // DEBUG

		}
	}
}

void ActionHoldingBall::End(Player* Player)
{
}
