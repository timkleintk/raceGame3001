// main cpp file or something

// copy pasted from sfml-dev.org

#include <SFML/Graphics.hpp>

#include "game.h"


int main()
{
    // time stuff
    sf::Clock clock;
    sf::Time elapsed = clock.restart();
    
    // setup window
    sf::RenderWindow window(sf::VideoMode(800, 600), "", sf::Style::None);
    
    // create game instance
    Game game(&window);
    game.Init();
    

    // main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            switch (event.type)
            {
            case sf::Event::Resized:
            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
            default:
                break;
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                game.onKeyDown(event);
                break;
            case sf::Event::KeyReleased:
                game.onKeyUp(event);
                break;
            case sf::Event::MouseButtonPressed:
                game.onMouseDown(event);
                break;
            case sf::Event::MouseButtonReleased:
                game.onMouseUp(event);
                break;
               
            }
        }
        
        // tick the game
        elapsed = clock.restart();
        game.tick(elapsed.asSeconds());

    }

    return 0;
}