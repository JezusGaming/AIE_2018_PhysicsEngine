#include "Rocket.h"

Rocket::Rocket(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : Sphere(position, velocity, mass, radius, colour)
{
}

Rocket::~Rocket()
{
}

bool Rocket::checkRocket(float dt)
{
	m_fTimer += dt;
	if (m_fTimer >= m_fFuelSpeed)
	{
		m_fTimer -= m_fFuelSpeed;
		m_mass -= m_fFuelConsumption;
		return true;
	}
	return false;
}
