#include "Rigidbody.h"
const static float MIN_LINEAR_THRESHOLD;
const static float MIN_ROTATION_THRESHOLD;

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float linearDrag, float angularDrag, float elasticity) : PhysicsObject(shapeID)
{
	m_postition = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
	m_elasticity = elasticity;
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_postition += m_velocity * timeStep;
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD) 
	{
		m_velocity = glm::vec2(0, 0);
	}
	if (glm::abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
	{
		m_angularVelocity = 0;
	}
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

void Rigidbody::resolveCollision(Rigidbody * actor2)
{
	glm::vec2 normal = actor2->getPostition() - m_postition;
	if(glm::length(normal) != 0)
		glm::normalize(normal);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;

	float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;

	float elasticaty = 1;
	float j = glm::dot(-(1 + elasticaty) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec2 force = normal * j;

	applyForceToActor(actor2, force);
}
