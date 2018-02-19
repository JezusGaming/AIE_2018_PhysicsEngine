#pragma once
#include "PhysicsObject3D.h"

class Rigidbody3D : public PhysicsObject3D
{
public:
	Rigidbody3D(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity, float rotation, float mass, float linearDrag, float angularDrag, float elasticity);
	~Rigidbody3D();

	virtual void fixedUpdate(glm::vec3 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec3 force);
	void applyForceToActor(Rigidbody3D* actor2, glm::vec3 force);

	//virtual bool CheckCollision(PhysicsObject* pOther) = 0;

	glm::vec3 getPostition() { return m_postition; }
	float getRotation() { return m_rotation; }
	glm::vec3 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	void setVelocity(glm::vec3 vel) { m_velocity = vel; }
	float getElasticity() { return m_elasticity; }
	void resolveCollision(Rigidbody3D* actor2);

protected:
	glm::vec3 m_postition;
	glm::vec3 m_velocity;
	float m_mass;
	float m_rotation; //2D so we only need a single float to represent our rotation
	float m_linearDrag;
	float m_angularDrag;
	float m_angularVelocity;
	float m_elasticity;
};

