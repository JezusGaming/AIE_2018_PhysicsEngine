#include "Sphere3D.h"
#include <Gizmos.h>


Sphere3D::Sphere3D(glm::vec3 position, glm::vec3 velocity, float mass, float radius, glm::vec4 colour) : Rigidbody3D(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
	m_moment = 0.5f * mass * radius * radius;
}

Sphere3D::Sphere3D(glm::vec3 position, float inclination, float speed, float mass, float radius, glm::vec4 colour) : Sphere3D(position, glm::vec3(sin(inclination), cos(inclination), tan(inclination)) * speed, mass, radius, colour)
{
}

Sphere3D::~Sphere3D()
{
}

void Sphere3D::makeGizmo()
{
	glm::vec3 end = glm::vec3(cos(m_rotation), sin(m_rotation), tan(m_rotation)) * m_radius;
	aie::Gizmos::addSphere(m_postition, m_radius, 12, 12, m_colour);
	aie::Gizmos::addLine(m_postition, m_postition + end, glm::vec4(1, 1, 1, 1));
}
