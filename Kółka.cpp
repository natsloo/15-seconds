#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Gra.h"
#include "Menu.h"
#include "Wyniki.h"
#include "Staty.h"

enum Sceny {
    menu,
    gra,
    wyniki,
    staty
};



int main()
{
    int counter = 0;
    setlocale(LC_CTYPE, "Polish");
    sf::RenderWindow okno(sf::VideoMode(1280, 720), "Circles");
    sf::Event e;
    int wybór = menu;
    Staty stat(okno);
    stat.loadFromFile();
    while (okno.isOpen()) {
        while (okno.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                stat.saveToFile();
                okno.close();
            }
            switch (wybór) {
            case menu: {
                Menu m(okno);
                wybór = m.run();
                break;
            }
            case gra: {
                Gra g(okno,stat);
                wybór = g.run();
                counter = g.getCounter();
                break;
            }
            case wyniki: {
                Wyniki w(okno,counter);
                wybór = w.run();
                break;
            }
            case staty: {
                wybór = stat.run();
                break;
            }
            }


        }
    }
    stat.saveToFile();
    return 0;
}
