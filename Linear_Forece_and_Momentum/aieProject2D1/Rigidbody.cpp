#include "Rigidbody.h"

Rigidbody::Rigidbody()
{
}

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
{
	m_postition = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_postition += m_velocity * timeStep;
}

void Rigidbody::debug()
{

}

void Rigidbody::applyForce(glm::vec2 force) 
{
	m_velocity += force / m_mass;
}

void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force) 
{
	actor2->applyForce(force);
	this->applyForce(-force);
}