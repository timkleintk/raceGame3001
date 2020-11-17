// main cpp file or something

// copy pasted from sfml-dev.org

#include <SFML/Graphics.hpp>

#include "game.h"


int main()
{
    // initialization
    Game game;


    // setup window
    sf::RenderWindow window(sf::VideoMode(200, 200), "Title");
    //window.setFramerateLimit(300);
    
    // time stuff
    sf::Clock clock;
    sf::Time elapsed = clock.restart();

    // variables
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);


    // tick
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
            // case sf::Event::
            // case sf::Event::
            // case sf::Event::
            default:
                break;
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                game.onKeyPress(event.key.code);
                //printf("keypress: %i\n", event.key.code);
                break;
            }
        }
        

        // calculate dt
        elapsed = clock.restart();
        game.tick(elapsed.asSeconds());

        
        

        // game code
        /*window.clear();
        window.draw(shape);
        window.display();*/
    }

    return 0;
}