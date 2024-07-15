#include "Wyniki.h"
#include "Button.h"
#include "Gra.h"
#include <iostream>

Wyniki::Wyniki(sf::RenderWindow& okno, int counter) : okno(okno), counter(counter) {
	if (!backgroundTexture.loadFromFile("assets/tlo3.jpg")) {
		exit(-1);
	}
	else {
		std::cout << "loaded background texture\n";
	}
	backgroundSprite.setTexture(backgroundTexture);

	sf::Vector2u windowSize = okno.getSize();
	sf::Vector2u textureSize = backgroundTexture.getSize();
	float scaleX = (float)windowSize.x / textureSize.x;
	float scaleY = (float)windowSize.y / textureSize.y;
	backgroundSprite.setScale(scaleX, scaleY);
}

int Wyniki::run() {
	sf::Font fontB;
	if (!fontB.loadFromFile("assets/andyb.ttf")) {
		exit(-1);
	}
	else {
		std::cout << "loaded wyniki fonts\n";
	}
	sf::Text wyniki;
	wyniki.setFont(fontB);
	wyniki.setFillColor(sf::Color::White);
	wyniki.setCharacterSize(50);
	wyniki.setPosition(545, 300);
	wyniki.setString("Score: " + std::to_string(counter));

	std::vector<Button> przyciski;
	sf::Vector2f buttonSize, button1pos, button2pos;
	buttonSize.x = 200;
	buttonSize.y = 100;
	button1pos.x = (1280 - buttonSize.x) / 2;
	button1pos.y = 400;
	button2pos.x = (1280 - buttonSize.x) / 2;
	button2pos.y = 400 + buttonSize.y + 20;

	sf::Color magenta;
	magenta = sf::Color::Magenta;

	std::string play = "PLAY AGAIN";
	std::string menu = "MENU";

	przyciski.emplace_back(buttonSize, magenta, button1pos, play, fontB);
	przyciski.emplace_back(buttonSize, magenta, button2pos, menu, fontB);

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
							return 0;
						}
					}
				}
				
			}
		}
		okno.clear();
		okno.draw(backgroundSprite);
		okno.draw(wyniki);
		for (int i = 0; i < przyciski.size(); i++) {
			okno.draw(przyciski[i]);
		}
		okno.display();
	}
	return 0;
}
