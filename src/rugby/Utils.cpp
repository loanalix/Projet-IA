#include "pch.h"
#include <SFML/System/Vector2.hpp>

#include <cmath>
#include <vector>
#include <string>
#include <random>

namespace Utils 
{

std::vector<std::string> Names{
"Billy",
    "Johny",
    "Willy",
    "Ronny",
    "Tommy",
    "Jimmy",
    "Timmy",
    //"Jerry",
    //"Terry",
    //"Larry",
    //"Harry",
    //"Barry",
    //"Gary",
    //"Pimy",
    //"Bobby",
    //"Ricky",
    //"Mikey",
   // "Freddy",
    "Kenny",
    // "Marty",
    // "Randy",
    // "Sammy",
    // "Toby",
    // "Tony",
    // "Vicky",
    // "Zachary",
    // "Andy",
    // "Brady",
    // "Casey",
    // "Cody",
    // "Corey",
    // "Davy",
    // "Eddy",
    // "Geoffrey",
    // "Gregory",
    // "Harvey",
    // "Jeffrey",
    // "Joey",
    // "Johnny",
    // "Kelsey",
    // "Lenny",
    // "Monty",
    // "Percy",
    // "Rodney",
    // "Rusty",
    // "Sidney",
     "Stanley",
     // "Teddy",
     // "Terry",
     // "Wesley",
     // "Wiley",
      "Dany",
      // "Dobby",
      // "Benny"
};

std::string getRandomName(bool getDuplicates = false) {
    // Générer un nombre aléatoire dans la plage des indices du vecteur
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> dist(0, Names.size() - 1);
    size_t index = dist(rng);
    std::string name = Names[index];

    if (!getDuplicates) {
        Names.erase(Names.begin() + index);
    }

    return name;
}


sf::Vector2f Vector2Normalize(const sf::Vector2f& vector)
{
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    if (magnitude == 0) {
        return { 0, 0 };
    }

    sf::Vector2f normalized = { vector.x / magnitude, vector.y / magnitude };

    return normalized;
}

float Vector2Magnitude(const sf::Vector2f& vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float GetDeltaTime()
{
    return 0.016f;
}

}
