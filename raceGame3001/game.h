#pragma once

#include <sfml/system/Vector2.hpp>
#include <SFML/Graphics.hpp>

typedef sf::Vector2f vec2;
typedef sf::Vector2<int> ivec;
typedef sf::Vector2<float> fvec;

#define PI 3.14159265358979323846

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