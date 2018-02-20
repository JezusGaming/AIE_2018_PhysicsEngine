#include "Plane3D.h"
#include <Gizmos.h>
#include <glm/ext.hpp>



Plane3D::Plane3D(glm::vec3 normal, float distance) : PhysicsObject3D(ShapeType::PLANE)
{
	m_distanceToOrigin = distance;
	m_normal = normal;
}


Plane3D::~Plane3D()
{
}

void Plane3D::fixedUpdate(glm::vec3 gravity, float timeStep)
{
}

void Plane3D::makeGizmo()
{
	float lineSegmentLength = 1;
	glm::vec3 parallel(m_normal.y, -m_normal.x , m_normal.z);
	glm::vec3 centerPoint = m_normal * m_distanceToOrigin;

	glm::vec4 colour(1, 1, 1, 1);
	glm::vec3 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec3 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::addAABBFilled(start, end, colour);
}

void Plane3D::resetPosition()
{
}

void Plane3D::resolveCollision(Rigidbody3D* actor2, glm::vec3 contact)
{
	// the plane isn't moving, so the relative velocity is just actor2's velocity
	glm::vec3 vRel = actor2->getVelocity();
	float e = actor2->getElasticity();
	float j = glm::dot(-(1 + e) * (vRel), m_normal) / (1 / actor2->getMass());

	glm::vec3 force = m_normal * j;

	actor2->applyForce(force, contact - actor2->getPostition());
}
