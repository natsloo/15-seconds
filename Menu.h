#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
	sf::RenderWindow& okno;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
public:
	Menu(sf::RenderWindow& okno);
	int run();
};

