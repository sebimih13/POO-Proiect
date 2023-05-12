#include <iostream>
#include <random>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#include "src/Game.h"
#include "src/ExceptionHierarchy.h"

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

    // Random seed
    srand(time(0));

    try
    {
        Game::GetInstance().Init();
    }
    catch (TextureError& err)
    {
        std::cout << err.what() << '\n';
        return -1;
    }
    catch (FontError& err)
    {
        std::cout << err.what() << '\n';
        return -1;
    }
    catch (GameError& err)
    {
        std::cout << err.what() << '\n';
        return -1;
    }
    catch (...)
    {
        std::cout << "Other Errors \n";
        return -1;
    }

    // Render Loop
    while (window.isOpen())
    {
        // Input
        sf::Event e;
        while (window.pollEvent(e))
        {
            Game::GetInstance().ProcessInput(e, window);
        }

        // Update
        Game::GetInstance().Update();

        // using namespace std::chrono_literals;
        // std::this_thread::sleep_for(300ms);

        // Draw
        window.clear();

        // Draw Scene
        Game::GetInstance().Draw(window);

        window.display();
    }

    return 0;
}

