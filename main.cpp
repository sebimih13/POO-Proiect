#include <iostream>

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
    Player1->ConsumeEnergy(4);
    Player1->RegenerateEnergy(1);
    Player1->TakeDamage(20);
    
    // Cards
    Player1->AddCard(new DamageCard(6, "assets/cards/Strike.png", "Strike", "Deal 10 damage", 1));
    Player1->AddCard(new DamageCard(6, "assets/cards/Strike.png", "Strike", "Deal 10 damage", 1));
    Player1->AddCard(new DamageCard(32, "assets/cards/Bludgeon.png", "Bludgeon", "Deal 32 damage", 3));
    Player1->AddCard(new ShieldCard(5, "assets/cards/Defend.png", "Defend", "Gain 5 Block", 1));
    Player1->AddCard(new ShieldCard(30, "assets/cards/Impervious.png", "Impervious", "Gain 30 Block", 2));

    // Items
    Player1->AddItem(new HealthPotion(10, "assets/items/BloodPotion.png", "Blood Potion", "Heal 10 HP"));
    Player1->AddItem(new BlockPotion(20, "assets/items/BlockPotion.png", "Block Potion", "Gain 20 Shield"));
    Player1->AddItem(new FullEnergyPotion("assets/items/EnergyPotion.png", "Energy Potion", "Regenerates your Energy"));
    Player1->AddItem(new MaxHealthPotion(50, "assets/items/HeartofIron.png", "Heart Of Iron", "Raise your max HP by 50"));

    // Print new stats
    std::cout << *Player1 << '\n';

    // Enemy
    Enemy* Enemy1 = new Enemy("El");

    Player1->SetCurrentEnemy(Enemy1);


    // TODO : End Turn Button
    sf::Texture EndTurnTexture;
    if (!EndTurnTexture.loadFromFile("assets/others/EndTurn.png"))     // TODO : ResourceManager
    {
        std::cout << "Can't load : assets/others/EndTurn.png";
    }
    
    sf::Sprite EndTurnSprite;
    EndTurnSprite.setTexture(EndTurnTexture);

    float EndTurnSpriteX = 1200.0f / 2.0f - EndTurnTexture.getSize().x / 2.0f;
    EndTurnSprite.setPosition(sf::Vector2f(EndTurnSpriteX, 10.0f));

    // TODO : Background
    sf::Texture BackgroundTexture;
    if (!BackgroundTexture.loadFromFile("assets/others/Background1.png"))
    {
        std::cout << "Can't load : assets/others/Background2.png";
    }

    sf::Sprite BackgroundSprite;
    BackgroundSprite.setTexture(BackgroundTexture);
    BackgroundSprite.setPosition(sf::Vector2f(0.0f, 0.0f));



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

        // Draw Background
        window.draw(BackgroundSprite);

        // Draw Buttons
        window.draw(EndTurnSprite);

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

