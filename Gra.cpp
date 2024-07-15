#include "Gra.h"
#include "Button.h"
#include "Staty.h"
#include <iostream>

Gra::Gra(sf::RenderWindow& okno, Staty& staty) : okno(okno), staty(staty), timerActive(false), counter(0), scoreAdded(false){
    if (!fontB.loadFromFile("assets/andyb.ttf")) {
        exit(-1);
    }
    else {
        std::cout << "loaded timer font\n";
    }
    timerText.setFont(fontB);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(1150, 10);

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




void Gra::drawTimer()
{
    if (timerActive) {
        sf::Time elapsed = clock.getElapsedTime();
        sf::Time remainingTime = sf::seconds(15) - elapsed;
        if (remainingTime.asSeconds() <= 0) {
            timerActive = false;
        }
        else {
            timerText.setString(std::to_string(remainingTime.asSeconds()));
            timerText.setOutlineColor(sf::Color::Black);
            timerText.setOutlineThickness(2);
        }
        okno.draw(timerText);
    }
}

void Gra::drawCounter() {
    counterText.setFont(fontB);
    counterText.setCharacterSize(30);
    counterText.setFillColor(sf::Color::White);
    counterText.setPosition(1150, 50);
    counterText.setOutlineColor(sf::Color::Black);
    counterText.setOutlineThickness(2);


    if (timerActive) {
        counterText.setString("Score: " + std::to_string(counter));
        okno.draw(counterText);
    }
}

void Gra::drawQuit() {
    quitText.setFont(fontB);
    quitText.setCharacterSize(30);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(30, 670);
    quitText.setOutlineColor(sf::Color::Black);
    quitText.setOutlineThickness(2);

    if (!timerActive) {
        quitText.setString("Press ESC anytime to return to Menu.");
        okno.draw(quitText);
    }
}

sf::CircleShape generator() {
    sf::CircleShape k�ko;
    int radius = rand() % 30 + 15;
    sf::Color kolor;
    kolor.r = rand() % 256;
    kolor.g = rand() % 256;
    kolor.b = rand() % 256;
    k�ko.setRadius(radius);
    k�ko.setFillColor(kolor);
    int x = rand() % (1280 - radius * 2);
    int y = rand() % (720 - radius * 2);
    k�ko.setPosition(x, y);
    return k�ko;
}

bool trafienie(int mx, int my, int radius, sf::Vector2f pozycja) {
    sf::Vector2f �rodek;
    �rodek.x = pozycja.x + radius;
    �rodek.y = pozycja.y + radius;
    if ((pow((mx - �rodek.x), 2) + pow((my - �rodek.y), 2)) <= pow(radius, 2)) {
        return true;
    }
    return false;
}

int Gra::getCounter() {
    return counter;
}

int Gra::run() {
    srand(time(0));

    std::vector<sf::CircleShape> k�ka;
    
    for (int i = 0; i < 25; i++) {
        k�ka.emplace_back(generator());
    }
    while (okno.isOpen()) {
        sf::Event e;
        okno.clear();
        if (!timerActive && clock.getElapsedTime().asSeconds() >= 15) {
            if (!scoreAdded) {
                staty.addScore(counter);
                staty.saveToFile();
                scoreAdded = true;
            }
            return 2;
        }
        while (okno.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                okno.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                for (int i = 0; i < k�ka.size(); i++) {
                    if (trafienie(e.mouseButton.x, e.mouseButton.y, k�ka[i].getRadius(), k�ka[i].getPosition())) {
                        counter++;
                        
                        std::cout << counter << std::endl;
                        k�ka.erase(k�ka.begin() + i);
                        k�ka.emplace_back(generator());
                        if (!timerActive) {
                            timerActive = true;
                        }
                        break;
                    }

                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                return 0;
            }
            
        }
        okno.draw(backgroundSprite);
        
        for (int i = 0; i < k�ka.size(); i++) {
            okno.draw(k�ka[i]);
        }
        drawTimer();
        drawCounter();
        drawQuit();
        okno.display();
    }
    return 0;
}

