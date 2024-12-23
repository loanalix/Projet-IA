#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.hpp"

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "GamingCampus - Rugby - IA/StateMachines");
    window.setFramerateLimit(60);


	GameManager * game_manager = GameManager::Instantiate();
    game_manager->setWindow(&window);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        window.clear();
        window.clear(sf::Color(51, 153, 102));

        
        game_manager->Draw();
        game_manager->Update();

        window.display();

        game_manager->setDeltaTime(dt.asSeconds());
    }
}
