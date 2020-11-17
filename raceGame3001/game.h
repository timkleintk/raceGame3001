#pragma once

namespace sf
{
class RenderWindow;
}

class Game
{
public:
	Game(sf::RenderWindow* w = 0) : m_window(w) {}
	~Game();

	void Init();
	//void setWindow(sf::RenderWindow* w);

	void tick(float dt);

	void onKeyPressed(int keycode);
	void onKeyReleased(int keycode);
	
private:
	sf::RenderWindow* m_window = 0;
	
};