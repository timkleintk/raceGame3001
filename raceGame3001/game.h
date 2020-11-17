#pragma once

namespace sf
{
class RenderWindow;
}

class Game
{
public:
	Game();
	~Game();

	void Init();
	//void setWindow(sf::RenderWindow* w);

	void tick(float dt);

	void onKeyPress(int keycode);
	
private:
	sf::RenderWindow* m_window;
	
};