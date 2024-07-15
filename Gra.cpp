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
    sf::CircleShape kó³ko;
    int radius = rand() % 30 + 15;
    sf::Color kolor;
    kolor.r = rand() % 256;
    kolor.g = rand() % 256;
    kolor.b = rand() % 256;
    kó³ko.setRadius(radius);
    kó³ko.setFillColor(kolor);
    int x = rand() % (1280 - radius * 2);
    int y = rand() % (720 - radius * 2);
    kó³ko.setPosition(x, y);
    return kó³ko;
}

bool trafienie(int mx, int my, int radius, sf::Vector2f pozycja) {
    sf::Vector2f œrodek;
    œrodek.x = pozycja.x + radius;
    œrodek.y = pozycja.y + radius;
    if ((pow((mx - œrodek.x), 2) + pow((my - œrodek.y), 2)) <= pow(radius, 2)) {
        return true;
    }
    return false;
}

int Gra::getCounter() {
    return counter;
}

int Gra::run() {
    srand(time(0));

    std::vector<sf::CircleShape> kó³ka;
    
    for (int i = 0; i < 25; i++) {
        kó³ka.emplace_back(generator());
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
                for (int i = 0; i < kó³ka.size(); i++) {
                    if (trafienie(e.mouseButton.x, e.mouseButton.y, kó³ka[i].getRadius(), kó³ka[i].getPosition())) {
                        counter++;
                        
                        std::cout << counter << std::endl;
                        kó³ka.erase(kó³ka.begin() + i);
                        kó³ka.emplace_back(generator());
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
        
        for (int i = 0; i < kó³ka.size(); i++) {
            okno.draw(kó³ka[i]);
        }
        drawTimer();
        drawCounter();
        drawQuit();
        okno.display();
    }
    return 0;
}

