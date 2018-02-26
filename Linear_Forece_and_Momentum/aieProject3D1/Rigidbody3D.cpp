#include "Rigidbody3D.h"
const static float MIN_LINEAR_THRESHOLD;
const static float MIN_ROTATION_THRESHOLD;

Rigidbody3D::Rigidbody3D(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity, float roation, float mass) : PhysicsObject3D(shapeID)
{
	m_postition = position;
	m_velocity = velocity;
	m_Rotation = roation;
	m_rotation = glm::mat4(1);
	m_mass = mass;
	m_linearDrag = 1.0f;
	m_angularDrag = 1.0f;
	m_elasticity = 0.8f;
	m_angularVelocity = glm::vec3(0.1f);
}

Rigidbody3D::~Rigidbody3D()
{
}

void Rigidbody3D::fixedUpdate(glm::vec3 gravity, float timeStep)
{
	glm::quat xRotation = glm::angleAxis(m_angularVelocity.x * timeStep, glm::vec3(1, 0, 0));
	glm::quat yRotation = glm::angleAxis(m_angularVelocity.y * timeStep, glm::vec3(0, 1, 0));
	glm::quat zRotation = glm::angleAxis(m_angularVelocity.z * timeStep, glm::vec3(0, 0, 1));

	glm::quat rotation = xRotation * yRotation * zRotation;

	m_rotation = glm::mat4_cast(rotation) * m_rotation;
	//applyForce(gravity * m_mass * timeStep);
	m_velocity += gravity * timeStep;
	m_postition += m_velocity * timeStep;
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD)
	{
		m_velocity = glm::vec3(0, 0, 0);
	}
	if (glm::length(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
	{
		m_angularVelocity = glm::vec3(0,0,0);
	}
}

void Rigidbody3D::debug()
{

}

void Rigidbody3D::applyForce(glm::vec3 force, glm::vec3 pos)
{
	m_velocity += force / m_mass;
	m_angularVelocity += (force.x * pos.y - 
						  force.x * pos.z -
						  force.y * pos.x -
						  force.y * pos.z -
						  force.z * pos.x -
						  force.z * pos.y) / (m_moment);
}

//void Rigidbody3D::applyForceToActor(Rigidbody3D* actor2, glm::vec3 force)
//{
//	actor2->applyForce(force);
//	this->applyForce(-force);
//}

void Rigidbody3D::resolveCollision(Rigidbody3D * actor2, glm::vec3 contact, glm::vec3* collisionormal)
{
	// find the vector between their centres, or use the provided direction 
	// of force
	glm::vec3 normal = collisionormal ? *collisionormal : glm::normalize(actor2->m_postition - m_postition);

	// get vetor perpendicular to the collision normal
	glm::vec3 perp(normal.y, -normal.x, normal.z);

	// detemine the total velocity of the contact points for the two objects, 
	// for both linear and rotational

	// 'r' is the radius from axis to application of force
	float r1 = glm::dot(contact - m_postition, -perp);
	float r2 = glm::dot(contact - actor2->m_postition, perp);
	// velocity of the contact point on this object
	float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity.x;
	// velocity of contact point on actor2
	float v2 = glm::dot(actor2->m_velocity, normal) + r2 * actor2->m_angularVelocity.x;

	if (v1 > v2) // they're moving closer
	{
		// calculate the effective mass at contact point for each object
		// ie how much the contact point will move due to the force applied.
		float mass1 = 1.0f / (1.0f / m_mass + (r1*r1) / m_moment);
		float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2*r2) / actor2->m_moment);

		float elasticaty = (m_elasticity + actor2->getElasticity()) / 2.0f;

		glm::vec3 force = (1.0f + elasticaty)*mass1*mass2 / (mass1 + mass2)*(v1 - v2)*normal;

		// apply equaln and opposite forces
		applyForce(-force, contact - m_postition);
		actor2->applyForce(force, contact - actor2->m_postition);
	}

	/*if (glm::length(normal) != 0)
		glm::normalize(normal);
	glm::vec3 relativeVelocity = actor2->getVelocity() - m_velocity;

	float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;

	float elasticaty = 1;
	float j = glm::dot(-(1 + elasticaty) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec3 force = normal * j;*/

	//applyForceToActor(actor2, force);
}
