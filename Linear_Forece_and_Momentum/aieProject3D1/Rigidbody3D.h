#pragma once
#include "PhysicsObject3D.h"

class Rigidbody3D : public PhysicsObject3D
{
public:
	Rigidbody3D(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity, float rotation, float mass);
	~Rigidbody3D();

	virtual void fixedUpdate(glm::vec3 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec3 force, glm::vec3 pos);
	//void applyForceToActor(Rigidbody3D* actor2, glm::vec3 force);

	//virtual bool CheckCollision(PhysicsObject* pOther) = 0;

	glm::vec3 getPostition() { return m_postition; }
	glm::mat4 getRotation() { return m_rotation; }
	float getrotation() { return m_Rotation; }
	glm::vec3 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	void setVelocity(glm::vec3 vel) { m_velocity = vel; }
	float getElasticity() { return m_elasticity; }
	void setPosition(glm::vec3 pos) { m_postition = pos; }
	void resolveCollision(Rigidbody3D* actor2, glm::vec3 contact, glm::vec3*collisionormal=nullptr);

protected:
	glm::vec3 m_postition;
	glm::vec3 m_velocity;
	float m_mass;
	glm::mat4 m_rotation; //2D so we only need a single float to represent our rotation
	float m_Rotation;
	float m_linearDrag;
	float m_angularDrag;
	glm::vec3 m_angularVelocity;
	float m_elasticity;
	float m_moment;
};

