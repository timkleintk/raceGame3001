#include "game.h"
#include <SFML/Graphics.hpp>


// i dont want to type sf::Vector2<float> all the time
typedef sf::Vector2f vec2;
typedef sf::Vector2<int> ivec;
typedef sf::Vector2<float> fvec;

sf::Texture* aTexture;
sf::Sprite* aSprite;


sf::RectangleShape* gui;
sf::Texture* guiTexture;


const sf::IntRect xButton(ivec(756, 12), ivec(30, 26));
const sf::IntRect grabWindow(ivec(8, 8), ivec(784, 36));
bool grabbedWindow = false;
ivec grabOffset;


void drawGUI(sf::RenderWindow* w)
{
	w->draw(*gui);
}

void Game::Init()
{
	// window stuff
	m_window->setFramerateLimit(300);
	//m_window->setSize(sf::Vector2u())


	// global variables
	aTexture = new sf::Texture();
	if (!aTexture->loadFromFile("assets/img/f1.png")) { printf("error loading in f1 car\n"); }
	aTexture->setSmooth(true);

	aSprite = new sf::Sprite();
	aSprite->setTexture(*aTexture);
	float scale = 1.0f;
	aSprite->setScale(scale, scale);




	guiTexture = new sf::Texture();
	if (!guiTexture->loadFromFile("assets/img/window.png")) { printf("error loading in window\n"); }
	gui = new sf::RectangleShape(vec2(m_window->getSize()));
	gui->setTexture(guiTexture);

}

void Game::tick(float dt)
{
	// moving the window?
	if (grabbedWindow) { m_window->setPosition(sf::Mouse::getPosition() + grabOffset); }

	// draw
	m_window->clear();
	drawGUI(m_window);
	
	//m_window->draw(*aSprite);

	m_window->display();
}

void Game::onKeyDown(sf::Event e)
{
	switch (e.key.code)
	{
	case sf::Keyboard::Escape:
		m_window->close();
		break;
	default:
		break;
	}
}

void Game::onKeyUp(sf::Event e)
{
	
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