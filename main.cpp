#include <iostream>
#include <cstdio>

#include "src/Character.h"
#include "src/Card.h"
#include "src/Item.h"

int main() 
{
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


    // End
    std::cout << "\nPress ENTER to continue\n";
    std::getchar();

    return 0;
}

