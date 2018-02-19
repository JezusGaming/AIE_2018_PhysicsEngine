#include "Plane.h"
#include <Gizmos.h>
#include <glm/ext.hpp>



Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(ShapeType::PLANE)
{	
	m_distanceToOrigin = distance;
	m_normal = normal;
}


Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::resetPosition()
{
}

void Plane::resolveCollision(Rigidbody* actor2)
{
	glm::vec2 normal = m_normal;

	if (glm::length(normal) != 0)
		glm::normalize(normal);

	glm::vec2 relativeVelocity = actor2->getVelocity();

	float elasticaty = 1;
	float j = glm::dot(-(1 + elasticaty) * (relativeVelocity), normal) / glm::dot(normal, normal * (1 / actor2->getMass()));

	glm::vec2 force = normal * j;

	actor2->applyForce(force);
}
