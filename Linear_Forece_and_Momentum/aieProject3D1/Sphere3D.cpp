#include "Sphere3D.h"
#include <Gizmos.h>

//----------------------------------------------------------------------------------------------
// constructer initializes values
//----------------------------------------------------------------------------------------------
Sphere3D::Sphere3D(glm::vec3 position, glm::vec3 velocity, float mass, float radius, glm::vec4 colour) : Rigidbody3D(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
	m_moment = 0.5f * mass * radius * radius;
}
//----------------------------------------------------------------------------------------------
// constructer initializes values like the other but has an extra value speed
//----------------------------------------------------------------------------------------------
Sphere3D::Sphere3D(glm::vec3 position, float inclination, float speed, float mass, float radius, glm::vec4 colour) : Sphere3D(position, glm::vec3(sin(inclination), cos(inclination), tan(inclination)) * speed, mass, radius, colour)
{
}
//----------------------------------------------------------------------------------------------
// defualt destructor
//----------------------------------------------------------------------------------------------
Sphere3D::~Sphere3D()
{
}
//----------------------------------------------------------------------------------------------
// Makes a plane and draws it
//----------------------------------------------------------------------------------------------
void Sphere3D::makeGizmo()
{
	aie::Gizmos::addSphere(m_postition, m_radius, 12, 12, m_colour);
}

