#include "Rigidbody3D.h"
const static float MIN_LINEAR_THRESHOLD;
const static float MIN_ROTATION_THRESHOLD;

Rigidbody3D::Rigidbody3D(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity, float rotation, float mass, float linearDrag, float angularDrag, float elasticity) : PhysicsObject3D(shapeID)
{
	m_postition = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
	m_elasticity = elasticity;
}


Rigidbody3D::~Rigidbody3D()
{
}

void Rigidbody3D::fixedUpdate(glm::vec3 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_postition += m_velocity * timeStep;
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD)
	{
		m_velocity = glm::vec3(0, 0, 0);
	}
	if (glm::abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
	{
		m_angularVelocity = 0;
	}
}

void Rigidbody3D::debug()
{

}

void Rigidbody3D::applyForce(glm::vec3 force)
{
	m_velocity += force / m_mass;
}

void Rigidbody3D::applyForceToActor(Rigidbody3D* actor2, glm::vec3 force)
{
	actor2->applyForce(force);
	this->applyForce(-force);
}

void Rigidbody3D::resolveCollision(Rigidbody3D * actor2)
{
	glm::vec3 normal = actor2->getPostition() - m_postition;
	if (glm::length(normal) != 0)
		glm::normalize(normal);
	glm::vec3 relativeVelocity = actor2->getVelocity() - m_velocity;

	float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;

	float elasticaty = 1;
	float j = glm::dot(-(1 + elasticaty) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec3 force = normal * j;

	applyForceToActor(actor2, force);
}
