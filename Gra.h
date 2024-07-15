#pragma once

#include <SFML/Graphics.hpp>
#include "Staty.h"

class Gra
{
	sf::RenderWindow& okno;
	bool timerActive;
	sf::Clock clock;
	sf::Time timer;
	sf::Text timerText;
	sf::Font fontB;
	int counter;
	sf::Text counterText;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Text quitText;
	Staty& staty;
	bool scoreAdded;
public:
	Gra(sf::RenderWindow& okno, Staty& staty);
	void drawTimer();
	int run();
	int getCounter();
	void drawCounter();
	void drawQuit();
};

