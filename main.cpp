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


    // Player
    Player* Player1 = new Player("Eu");
    std::cout << *Player1 << '\n';

    // Change stats
    Player1->IncreaseMaxHealth(10);
    Player1->Heal(10);
    Player1->TakeDamage(20);
    Player1->ConsumeEnergy(3);
    Player1->IncreaseShield(15);

    // Print new stats
    std::cout << *Player1 << '\n';

    // Enemy
    Enemy* Enemy1 = new Enemy("El");

    Player1->SetCurrentEnemy(Enemy1);


    while (window.isOpen())
    {
        // Input
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

            case sf::Event::MouseButtonPressed:
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "LEFT Mouse Button Pressed \n";

                    // Check Items + Cards
                    Player1->Select();
                }

                break;

            default:
                break;
            }
        }

        // Update
        Player1->Update(sf::Mouse::getPosition(window));

        //using namespace std::chrono_literals;
        //std::this_thread::sleep_for(300ms);

        window.clear();

        // Draw Scene

        // Draw Player
        Player1->Draw(window);

        // Draw Enemy
        Enemy1->Draw(window);
       
        window.display();
    }

    delete Player1;
    delete Enemy1;

    return 0;
}

