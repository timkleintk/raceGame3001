#pragma once

namespace sf
{
class RenderWindow;
class Event;
}

class Game
{
public:
	Game(sf::RenderWindow* w = 0) : m_window(w) {}
	~Game() {}

	void Init();
	//void setWindow(sf::RenderWindow* w);

	void tick(float dt);

	void onKeyDown(sf::Event);
	void onKeyUp(sf::Event);

	void onMouseDown(sf::Event);
	void onMouseUp(sf::Event);
	
private:
	sf::RenderWindow* m_window = 0;
	
};