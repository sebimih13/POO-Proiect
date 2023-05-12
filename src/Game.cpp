#include "Game.h"

#include "Character.h"
#include "Card.h"
#include "Item.h"
#include "ExceptionHierarchy.h"

#include <iostream>

// Initialization of static const
Game Game::Instance;

bool Game::EndGame = false;
unsigned int Game::CurrentLevel = 0;

Game::Game() : Player1(nullptr), Enemy1(nullptr), IsEndTurnButtonSelected(false), MaxLevel(9)
{
    std::cout << "New Game\n";
}

Game::~Game()
{

}

void Game::Init()
{
    // Load Font
    if (!Font.loadFromFile("assets/fonts/PoppinsRegular.ttf"))	// TODO : ResourceManager
    {
        throw FontError("assets/fonts/PoppinsRegular.ttf");
    }

    Player1 = std::make_shared<Player>("assets/characters/Ironclad.png", "Eu");
    Enemy1 = GetNextEnemy();

    // End Turn Button Norm + Hover
    if (!EndTurnNormTexture.loadFromFile("assets/others/endTurnButtonNorm.png"))     // TODO : ResourceManager
    {
        throw TextureError("assets/others/endTurnButtonNorm.png");
    }

    if (!EndTurnHoverTexture.loadFromFile("assets/others/endTurnButtonHover.png"))     // TODO : ResourceManager
    {
        throw TextureError("assets/others/endTurnButtonHover.png");
    }

    EndTurnSprite.setTexture(EndTurnNormTexture);

    float EndTurnSpriteX = 1200.0f / 2.0f - EndTurnNormTexture.getSize().x / 2.0f;
    EndTurnSprite.setPosition(sf::Vector2f(EndTurnSpriteX, -80.0f));

    // Background
    if (!BackgroundTexture.loadFromFile("assets/others/Background1.png"))       // TODO : ResourceManager
    {
        throw TextureError("assets/others/Background1.png");
    }

    BackgroundSprite.setTexture(BackgroundTexture);
    BackgroundSprite.setPosition(sf::Vector2f(0.0f, 0.0f));

    // Player
    std::cout << *Player1 << '\n';

    // Change stats
    Player1->ConsumeEnergy(1);
    Player1->RegenerateEnergy(1);

    // Cards
    Player1->AddCard(std::make_shared<DamageCard>(6, "assets/cards/Strike.png", "Strike", "Deal 6 damage", 1));
    Player1->AddCard(std::make_shared<DamageCard>(6, "assets/cards/Strike.png", "Strike", "Deal 6 damage", 1));
    Player1->AddCard(std::make_shared<DamageCard>(32, "assets/cards/Bludgeon.png", "Bludgeon", "Deal 32 damage", 3));
    Player1->AddCard(std::make_shared<ShieldCard>(5, "assets/cards/Defend.png", "Defend", "Gain 5 Block", 1));
    Player1->AddCard(std::make_shared<ShieldCard>(30, "assets/cards/Impervious.png", "Impervious", "Gain 30 Block", 2));

    // Items
    Player1->AddItem(std::make_shared<HealthPotion>(10, "assets/items/BloodPotion.png", "Blood Potion", "Heal 10 HP"));
    Player1->AddItem(std::make_shared<BlockPotion>(20, "assets/items/BlockPotion.png", "Block Potion", "Gain 20 Shield"));
    Player1->AddItem(std::make_shared<FullEnergyPotion>("assets/items/EnergyPotion.png", "Energy Potion", "Regenerates your Energy"));
    Player1->AddItem(std::make_shared<MaxHealthPotion>(50, "assets/items/HeartofIron.png", "Heart Of Iron", "Raise your max HP by 50"));

    // Print new stats
    std::cout << *Player1 << '\n';

    // Enemy
    Player1->SetCurrentEnemy(Enemy1);

    // Set Enemy Attack
    Enemy1->NewMove();

    // Get Current Cards
    Player1->NextCards();

    std::cout << *Enemy1 << '\n';
}

void Game::ProcessInput(const sf::Event& e, sf::RenderWindow& Window)
{
    if (e.type == sf::Event::Closed)
    {
        Window.close();
        return;
    }

    if (EndGame)
    {
        return;
    }

    // Update Cards/Items
    Player1->Update(sf::Mouse::getPosition(Window));

    // Update Button Texture
    if (490 <= sf::Mouse::getPosition(Window).x && sf::Mouse::getPosition(Window).x <= 705 &&
        10 <= sf::Mouse::getPosition(Window).y && sf::Mouse::getPosition(Window).y <= 90)
    {
        EndTurnSprite.setTexture(EndTurnHoverTexture);
        IsEndTurnButtonSelected = true;
    }
    else
    {
        EndTurnSprite.setTexture(EndTurnNormTexture);
        IsEndTurnButtonSelected = false;
    }

    switch (e.type)
    {
        case sf::Event::Resized:
            std::cout << "New width: " << Window.getSize().x << '\n'
                      << "New height: " << Window.getSize().y << '\n';
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

                if (IsEndTurnButtonSelected)
                {
                    // Enemy Move
                    Player1->TakeDamage(Enemy1->GetIncomingAttack());
                    Enemy1->IncreaseShield(Enemy1->GetIncomingShield());

                    // Reset Enemy Next Move
                    Enemy1->NewMove();

                    // Reset Player Energy + Cards
                    std::cout << "END TURN\n";
                    Player1->RegenerateFullEnergy();
                    Player1->NextCards();
                }
            }
            break;

        default:
            break;
    }
}

void Game::Update()
{
    if (EndGame)
    {
        return;
    }

    if (Player1->IsDead())
    {
        std::cout << "YOU DIED";
        EndGame = true;
    }

    if (Enemy1->IsDead())
    {
        std::cout << Enemy1->GetName() << " WAS DEFEATED\n";
        CurrentLevel++;

        if (CurrentLevel == MaxLevel)
        {
            std::cout << "WINNER\n";
            EndGame = true;
        }
        else
        {
            Enemy1 = GetNextEnemy();

            // Set Enemy
            Player1->SetCurrentEnemy(Enemy1);

            // Set Enemy Attack
            Enemy1->NewMove();

            // Reset Player Energy + Cards
            Player1->RegenerateFullEnergy();
            Player1->NextCards();
        }
    }
}

void Game::Draw(sf::RenderWindow& Window)
{
    // Draw Background
    Window.draw(BackgroundSprite);

    // Draw Buttons
    Window.draw(EndTurnSprite);

    // Draw Player
    Player1->Draw(Window);

    // Draw Enemy
    Enemy1->Draw(Window);

    // Draw VICTORY/DEFEAT screen
    if (EndGame)
    {
        sf::Text EndGameText;
        EndGameText.setFont(Font);
        EndGameText.setCharacterSize(250);
        EndGameText.setOutlineColor(sf::Color::Black);
        EndGameText.setOutlineThickness(8.0f);

        if (Player1->IsDead())
        {
            EndGameText.setString("DEFEAT");
            EndGameText.setFillColor(sf::Color::Red);
        }
        else
        {
            EndGameText.setString("VICTORY");
            EndGameText.setFillColor(sf::Color::Green);
        }

        float EndGameTextPosX = (1200.0f - EndGameText.getGlobalBounds().getSize().x) / 2.0f;
        EndGameText.setPosition(sf::Vector2f(EndGameTextPosX, 200.0f));

        Window.draw(EndGameText);
    }
}

std::shared_ptr<Enemy> Game::GetNextEnemy()
{
    switch (CurrentLevel)
    {
        case 0: return EnemyFactory::Gremlin();     break;
        case 1: return EnemyFactory::Book();        break;
        case 2: return EnemyFactory::Donut();       break;
        case 3: return EnemyFactory::Man();         break;
        case 4: return EnemyFactory::Slime();       break;
        case 5: return EnemyFactory::Guardian();    break;
        case 6: return EnemyFactory::Collector();   break;
        case 7: return EnemyFactory::Time();        break;
        case 8: return EnemyFactory::FinalBoss();   break;

        default: return EnemyFactory::Gremlin();    break;
    }
}

