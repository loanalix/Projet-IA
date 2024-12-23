#include "pch.h"
#include "ActionAttacking.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define PRIVACY_SPACE_RADIUS 75

void ActionAttacking::Start(Player* Player)
{
}

void ActionAttacking::Update(Player* player)
{
	// must stay behind the player with the ball
	
	Player* ballOwner = GameManager::Get()->getBall()->getOwner();


	switch (player->getTeam())
	{

	case Context::Team::Red:
		if (ballOwner != nullptr && GameManager::Get()->getBall()->getOwner()->getPosition().x + GameManager::Get()->getBall()->getOwner()->getSize() < player->getPosition().x)
		{
			sf::Vector2f direction = sf::Vector2f(-1, 0);
			player->setDirection(Utils::Vector2Normalize(direction));
		}
		else {
			sf::Vector2f direction = sf::Vector2f(1, 0);
			player->setDirection(Utils::Vector2Normalize(direction));
		}
		break;
	case Context::Team::Green:
		if (ballOwner != nullptr && GameManager::Get()->getBall()->getOwner()->getPosition().x - GameManager::Get()->getBall()->getOwner()->getSize() > player->getPosition().x)
		{
			sf::Vector2f direction = sf::Vector2f(1, 0);
			player->setDirection(Utils::Vector2Normalize(direction));
		}
		else {
			sf::Vector2f direction = sf::Vector2f(-1, 0);
			player->setDirection(Utils::Vector2Normalize(direction));
		}
		break;
	default:
		break;
	}

	// stay affar from allies
	std::vector<Player*> players = GameManager::Get()->getPlayers();
	for (auto p : players)
	{
		if (p != player && p->getTeam() == player->getTeam()) {

			sf::CircleShape privacySpace = sf::CircleShape();
			privacySpace.setRadius(PRIVACY_SPACE_RADIUS);
			privacySpace.setOrigin(PRIVACY_SPACE_RADIUS, PRIVACY_SPACE_RADIUS);
			privacySpace.setPosition(p->getPosition());
			privacySpace.setFillColor(sf::Color::Transparent);

#ifdef _DEBUG
			privacySpace.setOutlineColor(sf::Color::Green);
			privacySpace.setOutlineThickness(2);
			GameManager::Get()->getWindow()->draw(privacySpace);
#endif // _DEBUG
			if (player->getShape().getGlobalBounds().intersects(privacySpace.getGlobalBounds())) {
				//// Need to clamp movement speed to the player's speed

				sf::Vector2f dist = p->getPosition() - player->getPosition();
				sf::Vector2f norm = Utils::Vector2Normalize(dist);

				if (p->getState() != Context::State::HoldingBall && p->getState() != Context::State::Grace)
					p->setDirection(norm);
				if (player->getState() != Context::State::HoldingBall && player->getState() != Context::State::Grace)
					player->setDirection(-norm);
			}
		}
	}
}

void ActionAttacking::End(Player* Player)
{
}
