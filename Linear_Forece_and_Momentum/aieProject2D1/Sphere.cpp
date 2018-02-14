#include "Sphere.h"
#include <Gizmos.h>


Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : Rigidbody(SPHERE, position, velocity, 0, mass, 0.2f, 0.2f , 0.8f)
{
	m_radius = radius;
	m_colour = colour;
}

Sphere::Sphere(glm::vec2 position, float inclination, float speed, float mass, float radius, glm::vec4 colour) : Sphere(position, glm::vec2(sin(inclination), cos(inclination)) * speed, mass, radius, colour)
{
}


Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_postition, m_radius, 12, m_colour);
}

//bool Sphere::CheckCollision(PhysicsObject* pOther)
//{
//	Sphere* other = dynamic_cast<Sphere*>(pOther);
//	if (other)
//	{
//		return ((other->m_radius + this->m_radius) > glm::distance(other->m_postition, this->m_postition));
//	}
//	return false;
//}
