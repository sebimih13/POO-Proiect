#include <iostream>
#include <cstdio>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#include "src/Character.h"
#include "src/Card.h"
#include "src/Item.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

class SomeClass {
public:
    explicit SomeClass(int) {}
};

SomeClass *getC() {
    return new SomeClass{2};
}

int main() {
    #ifdef __linux__
    XInitThreads();
    #endif



    sf::RenderWindow window;
    // NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:30
    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);


    std::cout << "Hello, world!\n\n";

    // Player
    Character Player = Character("Eu");
    std::cout << Player << '\n';

    // Print Cards + Items
    Player.PrintCards();
    Player.PrintItems();

    // New Cards
    Card NewCard("NewCard");
    Player.AddCard(NewCard);

    // New Items
    Item NewItem("NewItem");
    Player.AddItem(NewItem);

    // Print Cards + Items
    Player.PrintCards();
    Player.PrintItems();

    // Change stats
    Player.IncreaseMaxHealth(10);
    Player.Heal(10);
    Player.TakeDamage(20);

    Player.ConsumeEnergy(1);

    Player.IncreaseShield(15);

    // Print new stats
    std::cout << Player << '\n';



    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            switch(e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
                break;
            case sf::Event::KeyPressed:
                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                break;
            default:
                break;
            }
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();
        window.display();
    }


    // End
    std::cout << "\nPress ENTER to continue\n";
    std::getchar();

    return 0;

}

