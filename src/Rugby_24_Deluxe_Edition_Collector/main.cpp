#include "pch.h"


int main(void)
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "GamingCampus - Rugby - IA/StateMachines");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("..\\..\\..\\src\\Rugby_24_Deluxe_Edition_Collector\\Assets\\Hack-Regular.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    sf::Texture StadiumTexture;
    if (!StadiumTexture.loadFromFile("..\\..\\..\\src\\Rugby_24_Deluxe_Edition_Collector\\Assets\\Stadium.png"))
    {
        std::cerr << "Failed to load WhiteTeam.png" << std::endl;
        return -1;
    }

    sf::Sprite StadiumSrpite;
     
    StadiumSrpite.setTexture(StadiumTexture);

	GameManager * game_manager = GameManager::Instantiate();
    game_manager->setWindow(&window);
    game_manager->init(font);

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
			game_manager->handleUserInput(event);
        }

        window.clear();
        window.clear(sf::Color(51, 153, 102));
        window.draw(StadiumSrpite);

        game_manager->Update();
        game_manager->Draw();

        

        window.display();

        game_manager->setDeltaTime(dt.asSeconds());
    }
}
