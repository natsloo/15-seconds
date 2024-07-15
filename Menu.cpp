#include "Menu.h"
#include "Button.h"
#include <iostream>
#include <cstdlib>

Menu::Menu(sf::RenderWindow& okno) : okno(okno) {
	if (!backgroundTexture.loadFromFile("assets/tlo3.jpg")) {
		exit(-1);
	}
	else {
		std::cout << "loaded background texture\n";
	}
	backgroundSprite.setTexture(backgroundTexture);

	sf::Vector2u windowSize = okno.getSize();
	sf::Vector2u textureSize = backgroundTexture.getSize();
	float scaleX = (float) windowSize.x / textureSize.x;
	float scaleY = (float) windowSize.y / textureSize.y;
	backgroundSprite.setScale(scaleX, scaleY);
}

int Menu::run() {
	
	sf::Font fontB, fontT;
	if (!fontB.loadFromFile("assets/andyb.ttf")){
		exit(-1);
	}
	else {
		std::cout << "loaded font\n";
	}
	if (!fontT.loadFromFile("assets/titlefont.ttf")) {
		exit(-1);
	}
	else {
		std::cout << "loaded title font\n";
	}
	std::vector<Button> przyciski;
	sf::Vector2f buttonSize, button1pos, button2pos, button3pos;
	sf::Color magenta;
	magenta = sf::Color::Magenta;
	buttonSize.x = 200;
	buttonSize.y = 100;
	button1pos.x = (1280 - buttonSize.x) / 2;
	button1pos.y = 300;
	button2pos.x = (1280 - buttonSize.x) / 2;
	button2pos.y = 300 + buttonSize.y + 20;
	button3pos.x = (1280 - buttonSize.x) / 2;
	button3pos.y = 300 + (buttonSize.y + 20) * 2;
	std::string play = "PLAY";
	std::string stats = "STATS";
	std::string exit = "EXIT";
	przyciski.emplace_back(buttonSize, magenta, button1pos, play, fontB);
	przyciski.emplace_back(buttonSize, magenta, button2pos, stats, fontB);
	przyciski.emplace_back(buttonSize, magenta, button3pos, exit, fontB);

	sf::Text tytu³;
	tytu³.setFont(fontT);
	tytu³.setFillColor(sf::Color::White);
	tytu³.setCharacterSize(70);
	tytu³.setPosition(450, 120);
	tytu³.setString("15 seconds");

	
	while (okno.isOpen()) {
		sf::Event e;
		while (okno.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				okno.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				for (int i = 0; i < przyciski.size(); i++) {
					sf::Vector2f mp; 
					mp.x = e.mouseButton.x;
					mp.y = e.mouseButton.y;
					if (przyciski[i].isClicked(mp)) {
						if (i == 0) {
							return 1;
						}
						else if (i == 1) {
							return 3;
						}
						else if (i == 2) {
							okno.close();
						}
					}
				}
			}
		}
		okno.clear();
		
		okno.draw(backgroundSprite);
		
		okno.draw(tytu³);
		
		for (int i = 0; i < przyciski.size(); i++) {
			okno.draw(przyciski[i]);
		}
		
		okno.display();
	}
	return 0;
}