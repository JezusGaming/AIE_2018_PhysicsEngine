#pragma once
#include "Rigidbody3D.h"
class Sphere3D : public Rigidbody3D
{
public:
	Sphere3D(glm::vec3 position, glm::vec3 velocity, float mass, float radius, glm::vec4 colour);
	Sphere3D(glm::vec3 position, float inclination, float speed, float mass, float radius, glm::vec4 colour);
	~Sphere3D();

	virtual void makeGizmo();
	//virtual bool CheckCollision(PhysicsObject* pOther);

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};

