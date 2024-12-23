#include "pch.h"
#include "ActionGrace.hpp"
#include <chrono>
#include "Player.hpp"
#include "Utils.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

void ActionGrace::Start(Player* Player)
{
	auto now = std::chrono::high_resolution_clock::now();
	mStartTime = std::chrono::duration<double>(now.time_since_epoch()).count();
	Player->setSpeed(Player->getGraceSpeed());

	if (Player->getTeam() == Context::Team::Green)
	{
		Player->setDirection(Utils::Vector2Normalize(sf::Vector2f(1, 0)));
	}
	else
	{
		Player->setDirection(Utils::Vector2Normalize(sf::Vector2f(-1, 0)));
	}
}

void ActionGrace::Update(Player* player)
{
	auto now = std::chrono::high_resolution_clock::now();
	double currentTime = std::chrono::duration<double>(now.time_since_epoch()).count();

	double elapsedTime = currentTime - mStartTime;
	if (elapsedTime >= player->getGraceTime())
	{
		// change state to holding ball
		player->setState(Context::State::HoldingBall);
	}

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
#endif // _DEBUG
		}
	}
}

void ActionGrace::End(Player* Player)
{
	Player->setSpeed(Player->getSpeed());
}
