#include "pch.h"

DebugClass::DebugClass()
{
	mPlayer = nullptr;

	toggleLine = false;
}

void DebugClass::Update()
{
	if (mPlayer != nullptr)
	{
		SetPlayerPositionOnMouse();
	}

	if (toggleLine)
		DebugShowTeammate();
}

void DebugClass::FindPlayer()
{
	if (mPlayer != nullptr)
	{
		ResetPlayer();
		return;
	}

	std::vector<Player*> players = GameManager::Get()->getPlayers();
	for (Player* player : players)
	{
		bool isPlayerSelected = player->getShape().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*GameManager::Get()->getWindow())));

		if (isPlayerSelected)
		{
			SetPlayer(player);
			break;
		}
	}
}

void DebugClass::ForceThrow() {
	Player* playerToThrow = nullptr;

	std::vector<Player*> players = GameManager::Get()->getPlayers();
	for (Player* player : players)
	{
		bool isPlayerSelected = player->getShape().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*GameManager::Get()->getWindow())));

		if (isPlayerSelected)
		{
			playerToThrow = player;
			break;
		}
	}

	Player* ballOwner = GameManager::Get()->getBall()->getOwner();

	if (playerToThrow != nullptr && ballOwner != nullptr && playerToThrow != ballOwner)
	{
		ballOwner->ThrowBall(playerToThrow);
	}
}

void DebugClass::SetPlayer(Player* player)
{
	mPlayer = player;
}

void DebugClass::ResetPlayer()
{
	mPlayer = nullptr;
}

void DebugClass::SetPlayerPositionOnMouse()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*GameManager::Get()->getWindow());
	mPlayer->setPosition(sf::Vector2f(mousePosition));
}

void DebugClass::handleUserInput(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		FindPlayer();
	}
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		ForceThrow();
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	{
		toggleLine = !toggleLine;
	}
}

void DebugClass::DebugShowTeammate()
{
	std::vector<Player*> tempTeam;
	std::vector<Player*> tempEnnemies;

	Player* main = GameManager::Get()->getBall()->getOwner();

	if (main != nullptr)
	{
		
		for (Player* player : GameManager::Get()->getPlayers())
		{
			if (GameManager::Get()->getBall()->getOwner() != player) {
				if (player->isBlack() == main->isBlack())
				{
					tempTeam.push_back(player);
				}
				else {
					tempEnnemies.push_back(player);
				}
			}
		}

		for (Player* teamate : tempTeam)
		{
			float dst = Utils::GetDistance(main->getPosition(), teamate->getPosition());

			float angle = atan2(teamate->getPosition().y - main->getPosition().y, teamate->getPosition().x - main->getPosition().x) * 180 / M_PI;

			sf::RectangleShape line(sf::Vector2f(dst, 2));
			line.setPosition(main->getPosition());
			line.rotate(angle);



			for (Player* ennemy : tempEnnemies) {

				if (ennemy->getShape().getGlobalBounds().intersects(line.getGlobalBounds()))
				{
					teamate->mOutlineThickness = false;
					line.setFillColor(sf::Color::Red);
					break;
				}
				else
				{
					teamate->mOutlineThickness = true;
					line.setFillColor(sf::Color::White);
				}
			}

			GameManager::Get()->getWindow()->draw(line);
		}
	}

}
