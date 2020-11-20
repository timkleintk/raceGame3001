#include "game.h"
#include "raceCar.h"
#include "camera.h"
#include <SFML/Graphics.hpp>

#include "map.h"


#include <fstream>
#include <iostream>

#define tireid 13
#define grassid 17
#define bracketid 65

#define slowDownSpeed 100.0f

using namespace sf;
using namespace std;

enum buttons { LEFT, RIGHT, UP, DOWN, NUMBUTTONS };
bool buttons[NUMBUTTONS] = { false };

Map map;

Texture* carTexture;
//Sprite* aSprite;

vector<RectangleShape*> tires;

RaceCar player;

Camera cam;

RectangleShape* gui;
Texture* guiTexture;

Font* font;
Text* lapTime;

RectangleShape* mapng;
Texture* mapTexture;
#define tileScale 1.0f

//fvec mapSize(1024, 512);

float timePassed = 0.0f;


const IntRect xButton(ivec(756, 12), ivec(30, 26));
const IntRect grabWindow(ivec(8, 8), ivec(784, 36));
bool grabbedWindow = false;
ivec grabOffset;


void Game::Init()
{
	// window stuff
	m_window->setFramerateLimit(300);
	//m_window->setSize(Vector2u())


	// global variables
	carTexture = new Texture();
	if (!carTexture->loadFromFile("assets/img/minicar.png")) { printf("error loading in the car\n"); }
	carTexture->setSmooth(true);
	player.getShape()->setTexture(carTexture);

	guiTexture = new Texture();
	if (!guiTexture->loadFromFile("assets/img/window.png")) { printf("error loading in window\n"); }
	gui = new RectangleShape(vec2(m_window->getSize()));
	gui->setTexture(guiTexture);

	mapTexture = new Texture();
	if (!mapTexture->loadFromFile("assets/img/racing.png")) { printf("error loading in the car\n"); }
	mapng = new RectangleShape(fvec(mapTexture->getSize())* tileScale);
	mapng->setTexture(mapTexture);

	fstream mapfile;
	char buffer[1024];
	mapfile.open("assets/maps/track1.csv", ios::in);
	fvec tPos;
	for (tPos.y = 0; tPos.y < mapng->getSize().y; tPos.y += TILESZ)
	{
		for (tPos.x = 0; tPos.x < mapng->getSize().x - TILESZ; tPos.x+= TILESZ)
		{
			//printf("(%f,%f)\n", tPos.x, tPos.y);
			mapfile.get(buffer, 1024, ',');
			if (parseInt(buffer) == grassid)
			{
				RectangleShape* r = new RectangleShape(fvec(TILESZ, TILESZ));
				r->setPosition(tPos);
				tires.push_back(r);
			}
			else if (parseInt(buffer) == bracketid)
			{
				player.getShape()->setPosition(fvec(tPos.x,tPos.y));
				player.getShape()->setRotation(180);
			
			}
			mapfile.get();
		}
		mapfile.get(buffer, 1024);
		if (parseInt(buffer) == tireid)
		{
			RectangleShape* r = new RectangleShape(fvec(TILESZ, TILESZ));
			r->setPosition(tPos);
			tires.push_back(r);
		}
		mapfile.get();
	}
	mapfile.close();
	//tires.push_back(new RectangleShape(fvec(TILESZ, TILESZ)));

	font = new Font;
	if (!font->loadFromFile("assets/font/arial.ttf")) { printf("error loading in the font\n"); }

	lapTime = new Text;
	lapTime->setFont(*font);
	lapTime->setPosition(fvec(100, 100));
	lapTime->setCharacterSize(24);
	

	// cam
	cam.setTarget(m_window);

}

void Game::tick(float dt)
{

	timePassed += dt;
	// moving the window?
	if (grabbedWindow) { m_window->setPosition(Mouse::getPosition() + grabOffset); }



	// draw
	m_window->clear();
	cam.draw(gui, HUD);
	//cam.draw(gui, BACKGROUND);
	cam.draw(mapng, BACKGROUND);
	//m_window->draw(*gui);

	if (buttons[LEFT]) { player.turn(-1, dt); }
	if (buttons[RIGHT]) { player.turn(1, dt); }
	if (buttons[UP]) { player.accelerate(dt); }
	if (buttons[DOWN]) { player.brake(dt); }
	//player.applyForce(fvec(1, 0));
	player.update(dt);
	for (auto t : tires)
	{
		//RectangleShape rect(fvec(TILESZ, TILESZ));
		//rect.setPosition(fvec(t->left, t->top));
		
		//m_window->draw(RectangleShape(fvec(TILESZ, TILESZ)).setPosition(fvec(t->left, t->top)));
		//m_window->draw(*t);
		//cam.draw(t, FOREGROUND);
		FloatRect intersection;
		if (player.getShape()->getGlobalBounds().intersects(t->getGlobalBounds(), intersection))
		{
			player.brake(dt);
			player.accelerate(dt);
		}
	}
	//player.draw(m_window);
	cam.draw(player.getShape(), MIDDLE);
	//m_window->draw(*aSprite);

	char str[] = "Laptime: 00000.00";
	sprintf_s(str, "Laptime:%.2f", timePassed);
	lapTime->setString(str);
	
	cam.draw(lapTime, HUD);
	
	cam.follow(&player);
	cam.draw();
	//m_window->display();
}

void Game::onKeyDown(Event e)
{
	switch (e.key.code)
	{
	case Keyboard::Escape: m_window->close(); break;
	case 71: buttons[LEFT] = true; break;
	case 72: buttons[RIGHT] = true;	break;
	case 73: buttons[UP] = true; break;
	case 74: buttons[DOWN] = true; break;
	default: printf("key %i pressed\n", e.key.code); break;
	}
}

void Game::onKeyUp(Event e)
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

void Game::onMouseDown(Event e)
{
	if (e.mouseButton.button == Mouse::Left)
	{
		//if (e.mouseButton.x)
		if (xButton.contains(e.mouseButton.x, e.mouseButton.y)) { m_window->close(); }
		if (grabWindow.contains(e.mouseButton.x, e.mouseButton.y)) { grabbedWindow = true; grabOffset = m_window->getPosition() - Mouse::getPosition();
		}
	}
}

void Game::onMouseUp(Event e)
{
	if (grabbedWindow) { grabbedWindow = false; m_window->setPosition(Mouse::getPosition() + grabOffset); }
}