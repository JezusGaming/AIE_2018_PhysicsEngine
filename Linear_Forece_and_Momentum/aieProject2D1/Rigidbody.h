#pragma once
#include "PhysicsObject.h"
class Rigidbody : public PhysicsObject
{
public:
	Rigidbody();
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	~Rigidbody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec2 force);
	void applyForceToActor(Rigidbody* actor2, glm::vec2 force);

	//virtual bool CheckCollision(PhysicsObject* pOther) = 0;

	glm::vec2 getPostition() { return m_postition; }
	float getRotation() { return m_rotation; }
	glm::vec2 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }


protected:
	glm::vec2 m_postition;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation; //2D so we only need a single float to represent our rotation
};

