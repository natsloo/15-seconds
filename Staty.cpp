#include "Staty.h"
#include <fstream>
#include <iostream>
#include <sstream>

Staty::Staty(sf::RenderWindow& okno) : okno(okno), highscore(0) {
    if (!fontB.loadFromFile("assets/andyb.ttf")) {
        exit(-1);
    }
    else {
        std::cout << "loaded font\n";
    }
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

void Staty::addScore(int score) {
    sessionScores.push_back(score);
    if (score > highscore) {
        highscore = score;
    }
    std::cout << "Score added: " << score << std::endl;
    std::cout << "Current sessionScores: ";
    for (int s : sessionScores) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

std::vector<int> Staty::getScores() {
    return sessionScores;
}

int Staty::getHighscore() {
    return highscore;
}

void Staty::saveToFile() {
    std::ofstream saver("stats.txt");
    if (saver.is_open()) {
        saver << highscore<<std::endl;
        saver.close();
    }
    else {
        std::cerr << "saver failed to open stats.txt" << std::endl;
    }
}

void Staty::loadFromFile() {
    std::ifstream loader("stats.txt");
    if (loader.is_open()) {
        loader >> highscore;
        loader.close();
        std::cout << "Loaded highscore: " << highscore << std::endl;
    }
    else {
        std::cerr << "loader failed to open stats.txt" << std::endl;
    }
    
}

void Staty::drawQuit() {
    quitText.setFont(fontB);
    quitText.setCharacterSize(30);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(30, 670);
    quitText.setOutlineColor(sf::Color::Black);
    quitText.setOutlineThickness(2);
    quitText.setString("Press ESC to return to Menu.");
    okno.draw(quitText);
}

std::string Staty::vectorToString() {
    std::stringstream ss;
    for (int score : sessionScores) {
        ss << score << ", ";
    }
    std::cout << ss.str();
    std::string result = ss.str();
    if (!result.empty()) {
        result.pop_back(); // Remove trailing space
        result.pop_back(); // Remove trailing comma
    }
    return result;
}

int Staty::run() {
    sf::Text score, sessionS;
    score.setFont(fontB);
    score.setFillColor(sf::Color::White);
    score.setCharacterSize(55);
    score.setPosition(30, 250);
    score.setOutlineColor(sf::Color::Black);
    score.setOutlineThickness(2);
    

    sessionS.setFont(fontB);
    sessionS.setFillColor(sf::Color::White);
    sessionS.setCharacterSize(40);
    sessionS.setPosition(30, 350);
    sessionS.setOutlineColor(sf::Color::Black);
    sessionS.setOutlineThickness(2);
    
    loadFromFile();
	while (okno.isOpen()) {
		sf::Event e;
		while (okno.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				okno.close();
			}
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return 0;
        }
        okno.clear();
        okno.draw(backgroundSprite);
        score.setString("Highscore: " + std::to_string(getHighscore()));
        okno.draw(score);
        sessionS.setString("Session scores: " + vectorToString());
        okno.draw(sessionS);
        drawQuit();
        okno.display();
		
	}
    return 0;
}