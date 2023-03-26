#include <iostream>
#include <cstdio>

#include "src/Character.h"

int main() 
{
    std::cout << "Hello, world!\n\n";

    // Player
    Character Player = Character("Eu");
    std::cout << Player << '\n';

    Player.PrintCards();
    Player.PrintItems();

    // End
    std::cout << "\nPress ENTER to continue\n";
    std::getchar();

    return 0;
}

