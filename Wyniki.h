#pragma once

#include <SFML/Graphics.hpp>

class Wyniki
{
	sf::RenderWindow& okno;
	int counter;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
public:
	Wyniki(sf::RenderWindow& okno, int counter);
	int run();
};

