#include "game.h"
#include "raceCar.h"
#include "camera.h"
#include <SFML/Graphics.hpp>


enum buttons { LEFT, RIGHT, UP, DOWN, NUMBUTTONS };
bool buttons[NUMBUTTONS] = { false };


sf::Texture* carTexture;
//sf::Sprite* aSprite;

RaceCar player;

Camera cam;

sf::RectangleShape* gui;
sf::Texture* guiTexture;


const sf::IntRect xButton(ivec(756, 12), ivec(30, 26));
const sf::IntRect grabWindow(ivec(8, 8), ivec(784, 36));
bool grabbedWindow = false;
ivec grabOffset;


void Game::Init()
{
	// window stuff
	m_window->setFramerateLimit(300);
	//m_window->setSize(sf::Vector2u())


	// global variables
	carTexture = new sf::Texture();
	if (!carTexture->loadFromFile("assets/img/minicar.png")) { printf("error loading in the car\n"); }
	carTexture->setSmooth(true);
	player.getShape()->setTexture(carTexture);


	guiTexture = new sf::Texture();
	if (!guiTexture->loadFromFile("assets/img/window.png")) { printf("error loading in window\n"); }
	gui = new sf::RectangleShape(vec2(m_window->getSize()));
	gui->setTexture(guiTexture);

	// cam
	cam.setTarget(m_window);

}

void Game::tick(float dt)
{
	// moving the window?
	if (grabbedWindow) { m_window->setPosition(sf::Mouse::getPosition() + grabOffset); }

	// draw
	m_window->clear();
	cam.draw(gui, HUD);
	cam.draw(gui, BACKGROUND);
	//m_window->draw(*gui);

	if (buttons[LEFT]) { player.turn(-1, dt); }
	if (buttons[RIGHT]) { player.turn(1, dt); }
	if (buttons[UP]) { player.accelerate(dt); }
	if (buttons[DOWN]) { player.brake(dt); }
	//player.applyForce(fvec(1, 0));
	player.update(dt);
	//player.draw(m_window);
	cam.draw(player.getShape(), MIDDLE);
	//m_window->draw(*aSprite);

	cam.follow(&player);
	cam.draw();
	//m_window->display();
}

void Game::onKeyDown(sf::Event e)
{
	switch (e.key.code)
	{
	case sf::Keyboard::Escape: m_window->close(); break;
	case 71: buttons[LEFT] = true; break;
	case 72: buttons[RIGHT] = true;	break;
	case 73: buttons[UP] = true; break;
	case 74: buttons[DOWN] = true; break;
	default: printf("key %i pressed\n", e.key.code); break;
	}
}

void Game::onKeyUp(sf::Event e)
{
	switch (e.key.code)
	{
	case 71: buttons[LEFT] = false; break;
	case 72: buttons[RIGHT] = false; break;
	case 73: buttons[UP] = false; break;
	case 74: buttons[DOWN] = false; break;

	default: break;
	}
}

void Game::onMouseDown(sf::Event e)
{
	if (e.mouseButton.button == sf::Mouse::Left)
	{
		//if (e.mouseButton.x)
		if (xButton.contains(e.mouseButton.x, e.mouseButton.y)) { m_window->close(); }
		if (grabWindow.contains(e.mouseButton.x, e.mouseButton.y)) { grabbedWindow = true; grabOffset = m_window->getPosition() - sf::Mouse::getPosition();
		}
	}
}

void Game::onMouseUp(sf::Event e)
{
	if (grabbedWindow) { grabbedWindow = false; m_window->setPosition(sf::Mouse::getPosition() + grabOffset); }
}