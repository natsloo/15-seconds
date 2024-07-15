#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

class Staty
{
	sf::RenderWindow& okno;
	std::vector<int> sessionScores;
	int highscore;
	sf::Text quitText;
	sf::Font fontB;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:
	Staty(sf::RenderWindow& okno);
	int run();
	void addScore(int score);
	std::vector<int> getScores();
	int getHighscore();
	void saveToFile();
	void loadFromFile();
	void drawQuit();
	std::string vectorToString();
};