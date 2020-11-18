#include <sfml/Graphics.hpp>
#include "game.h"
#include "camera.h"
#include "racecar.h"

using namespace sf;

Camera::Camera()
{
	
}

void Camera::follow(RaceCar* r)
{
	
	m_transformable.setPosition(r->getShape()->getPosition());
	m_transformable.setRotation(r->getShape()->getRotation());
	m_transformable.rotate(90.0f);
	//m_transformable.rot
	
	fvec rpos = r->getShape()->getPosition();
	//m_transform.translate(fvec(1, 2));
	fvec cpos = *((fvec*)(&m_transform.getMatrix()[12])); // why the fuck does this work?
	fvec offset = rpos - cpos;

	m_transform.translate(offset);
	
	//m_transform = r->getShape()->getTransform();
	

	//float rr = r->getShape()->getRotation();
	//float cr = m_transform.

}

void Camera::draw(Drawable* d, int z)
{
	queues[z].push_back(d);
}


void Camera::draw()
{
	Transform offset = m_transformable.getInverseTransform();
	for (int z = 0; z < NUMLEVELS; z++)
	{
		if (z == HUD) { offset = Transform(); }
		for (Drawable*& d : queues[z])
		{
			//offset.translate(fvec(m_window->getSize()) / 2.0f);
			//m_window->draw(*d, m_transform.getInverse().translate(fvec(m_window->getSize()) / 2.0f));
			m_window->draw(*d, offset);
			
		}
		queues[z].clear();
	}
	m_window->display();
}