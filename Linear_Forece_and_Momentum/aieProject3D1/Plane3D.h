#pragma once
#include "PhysicsObject3D.h"
#include "Rigidbody3D.h"
class Plane3D : public PhysicsObject3D
{
public:
	Plane3D(glm::vec3 normal, float distance);
	~Plane3D();

	virtual void fixedUpdate(glm::vec3 gravity, float timeStep);
	virtual void debug() {}
	virtual void makeGizmo();
	virtual void resetPosition();

	glm::vec3 getNormal() { return m_normal; }
	float getDistance() { return m_distanceToOrigin; }
	void resolveCollision(Rigidbody3D* actor2);

protected:
	glm::vec3 m_normal;
	float m_distanceToOrigin;
};

