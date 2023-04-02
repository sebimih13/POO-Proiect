#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#include "src/Character.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

int main() 
{
    #ifdef __linux__
    XInitThreads();
    #endif

    sf::RenderWindow window;
    // NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:30
    window.create(sf::VideoMode({1200, 800}), "Card Game", sf::Style::Default);
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
    Card NewCard("assets/cards/Strike.png");
    Player.AddCard(NewCard);

    // New Items
    Item NewItem("assets/items/BloodPotion.png", "Blood Potion", "Heal 20 HP");
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


    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            switch (e.type)
            {
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

        // Draw Scene

        // Draw Player
        Player.Draw(window);

        // TODO : Draw Enemy

       

        window.display();
    }

    return 0;
}

