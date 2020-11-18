#pragma once

#include <sfml/Graphics.hpp>
class RaceCar;

using namespace sf;

enum zLevels { BACKGROUND, MIDDLE, FOREGROUND, HUD, NUMLEVELS };

class Camera
{
public:
	Camera();

	void follow(RaceCar* r);

	void setTarget(RenderWindow* w) { m_window = w; m_transformable.setOrigin(fvec(m_window->getSize()) / 2.0f);
	}
	void draw(Drawable* d, int z = BACKGROUND);
	void drawHud();
	void draw();

	fvec getPos() const { return m_transformable.getPosition(); }
	ivec getSize() const { return ivec(m_window->getSize()); }

private:
	std::vector<Drawable*> queues[NUMLEVELS];

	//fvec m_pos;
	Transform m_transform;
	Transformable m_transformable;

	RenderWindow* m_window = 0;
};