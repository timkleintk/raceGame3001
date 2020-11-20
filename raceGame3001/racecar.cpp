#include <SFML/Graphics.hpp>
#include "game.h"
#include "racecar.h"

#define carscale 1.0f



float turnspeed = 1.0f;
float acceleration = 200.0f;
float brakingForce = 300.0f;
float maxVel = 500.0f;

void RaceCar::update(float dt)
{
	if (m_vel > maxVel) { m_vel = maxVel; }

	float r = m_shape.getRotation() / 180.0f * PI;
	fvec vel(cosf(r) * m_vel, sinf(r) * m_vel);
	//vel += m_force * dt / m_mass;
	//m_force.x = m_force.y = 0;
	m_shape.move(vel * dt);

}

RaceCar::RaceCar()
{
	m_shape = RectangleShape(fvec(32, 22) * carscale);
	m_shape.setOrigin(fvec(16, 11));
	m_shape.setPosition(fvec(100, 100));
}

void RaceCar::draw(RenderWindow* w)
{
	w->draw(m_shape);
}

void RaceCar::turn(float d, float dt)
{
	m_shape.rotate(turnspeed * (maxVel - m_vel) * d * dt);
}

void RaceCar::accelerate(float dt)
{
	m_vel += acceleration * dt;
}


void RaceCar::brake(float dt)
{
	if (m_vel < 0) { m_vel = 0; }
	else { m_vel -= brakingForce * dt; }
}