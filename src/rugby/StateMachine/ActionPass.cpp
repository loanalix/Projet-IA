#include "pch.h"
#include "ActionPass.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <chrono>
#include <iostream>

void ActionPass::Start(Player* player)
{
	auto now = std::chrono::high_resolution_clock::now();
	mStartTime = std::chrono::duration<double>(now.time_since_epoch()).count();
}

void ActionPass::Update(Player* player)
{
	auto now = std::chrono::high_resolution_clock::now();
	double currentTime = std::chrono::duration<double>(now.time_since_epoch()).count();

	double elapsedTime = currentTime - mStartTime;
	if (elapsedTime >= player->getGraceTime())
	{
		player->setState(Context::State::Fetch);
		return;
	}

	// continue rushing the enemy base
	if (player->getTeam() == Context::Team::Green)
	{
		player->setDirection(Utils::Vector2Normalize(sf::Vector2f(1, 0)));
	}
	else
	{
		player->setDirection(Utils::Vector2Normalize(sf::Vector2f(-1, 0)));
	}

	// if you are not the owner of the ball, don't bother
	if (GameManager::Get()->getBall()->getOwner() != player)
	{
		//std::cout << "Wait I can't do that\n";
		return;
	}

	std::vector<Player*> players = GameManager::Get()->getPlayers();

	float nearestDistance = 1000000;
	Player* nearestPlayer = nullptr;


	bool possible = true;
	for (auto p : players) {
		if (p != player && p->getTeam() == player->getTeam()) {


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

			if (possible) { // throw ball at the nearest player
				line.setFillColor(sf::Color::Blue);
				if (Utils::Vector2Magnitude(p->getPosition() - player->getPosition()) < nearestDistance) {
					if (player->getTeam() == Context::Team::Red && p->getPosition().x > player->getPosition().x) {
						nearestDistance = Utils::Vector2Magnitude(player->getPosition() - p->getPosition());
						nearestPlayer = p;
					}
					else if (player->getTeam() == Context::Team::Green && p->getPosition().x < player->getPosition().x) {
						nearestDistance = Utils::Vector2Magnitude(player->getPosition() - p->getPosition());
						nearestPlayer = p;
					}
					else {
						line.setFillColor(sf::Color::Red);
					}
				}
			}
			else {
				line.setFillColor(sf::Color::Red);
			}
#ifdef _DEBUG
			GameManager::Get()->getWindow()->draw(line);
#endif // _DEBUG
		}
	}

	// pass the ball to the nearest player

	Ball* ball = GameManager::Get()->getBall();
	if (possible && nearestPlayer != nullptr) {
		ball->throwAt(nearestPlayer, player->getThrowSpeed());
	}
}

void ActionPass::End(Player* Player)
{
}
