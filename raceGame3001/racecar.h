#pragma once

#include "game.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class RaceCar
{
public:
	RaceCar();
	~RaceCar() {};

	void update(float dt);

	void applyForce(fvec f) { m_force += f; };

	RectangleShape* getShape() { return &m_shape; }

	void draw(RenderWindow* w);

	void turn(float d, float dt);

	void accelerate(float dt);

	void brake(float dt);
	
	//void rotate(float r) { m_shape.rotate(r); }
	
	//void turn(int d);
	
private:
	RectangleShape m_shape;
	float m_vel = 0.0f;
	fvec m_force = fvec(0, 0);
	float m_mass = 1.0f;
};