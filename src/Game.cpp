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

const std::vector<std::shared_ptr<EnemyInfo>> Game::LevelEnemy = {
    std::make_shared<EnemyInfo>("assets/characters/GremlinLeader.png",            "Gremlin",        100, 5),
    std::make_shared<EnemyInfo>("assets/characters/Book-of-stabbing-pretty.png",  "Book",           120, 5),
    std::make_shared<EnemyInfo>("assets/characters/Donu.png",                     "Donut",          110, 10),
    std::make_shared<EnemyInfo>("assets/characters/Slaver-blue-pretty.png",       "Man",             70, 10),
    std::make_shared<EnemyInfo>("assets/characters/slime.png",                    "Slime",          140, 15),
    std::make_shared<EnemyInfo>("assets/characters/Spheric-guardian-pretty.png",  "Guardian",       150, 15),
    std::make_shared<EnemyInfo>("assets/characters/TheCollector.png",             "Collector",      200, 20),
    std::make_shared<EnemyInfo>("assets/characters/Time-eater-pretty.png",        "Time",           210, 20),
    std::make_shared<EnemyInfo>("assets/characters/Champ.png",                    "Final Boss",     250, 25)
};

Game::Game() : Player1(nullptr), Enemy1(nullptr), IsEndTurnButtonSelected(false)
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

    Player1 = std::make_unique<Player>("assets/characters/Ironclad.png", "Eu");
    Enemy1 = std::make_unique<Enemy>(LevelEnemy[CurrentLevel]->FilePath, LevelEnemy[CurrentLevel]->Name, LevelEnemy[CurrentLevel]->MaxHealth, 0, LevelEnemy[CurrentLevel]->MaxMove);
    IsEndTurnButtonSelected = false;

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
    Player1->SetCurrentEnemy(Enemy1.get());

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
        std::cout << LevelEnemy[CurrentLevel]->Name << " WAS DEFEATED\n";
        CurrentLevel++;

        if (CurrentLevel == LevelEnemy.size())
        {
            std::cout << "WINNER\n";
            EndGame = true;
        }
        else
        {
            Enemy1 = std::make_unique<Enemy>(LevelEnemy[CurrentLevel]->FilePath, LevelEnemy[CurrentLevel]->Name, LevelEnemy[CurrentLevel]->MaxHealth, 0, LevelEnemy[CurrentLevel]->MaxMove);

            // Set Enemy
            Player1->SetCurrentEnemy(Enemy1.get());

            // Set Enemy Attack
            Enemy1->NewMove();

            // Reset Player Energy + Cards
            Player1->RegenerateFullEnergy();
            Player1->NextCards();
        }

        int i = 1;
        i++;
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

