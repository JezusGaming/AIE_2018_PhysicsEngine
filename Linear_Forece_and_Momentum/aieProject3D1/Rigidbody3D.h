#pragma once
#include "PhysicsObject3D.h"

class Rigidbody3D : public PhysicsObject3D
{
public:
	//----------------------------------------------------------------------------------------------
	// constructer initializes values
	//----------------------------------------------------------------------------------------------
	Rigidbody3D(ShapeType shapeID, glm::vec3 position, glm::vec3 velocity, float rotation, float mass);
	//----------------------------------------------------------------------------------------------
	// defualt destructor
	//----------------------------------------------------------------------------------------------
	~Rigidbody3D();
	//----------------------------------------------------------------------------------------------
	// Updates the rigidbody and it velocity, postion, rotation, and angularvelocity every frame
	//
	// Param:
	//		gravity: A vec3 which sets Rigidbody m_gravity to help apply velocity to objects
	//		timeStep: A float which sets Rigidbody m_timeStep to help apply velocity to objects ect
	//----------------------------------------------------------------------------------------------
	virtual void fixedUpdate(glm::vec3 gravity, float timeStep);
	//----------------------------------------------------------------------------------------------
	// Used only for debug purpose
	//----------------------------------------------------------------------------------------------
	virtual void debug();
	//----------------------------------------------------------------------------------------------
	// Applies force to the rigidbody
	//
	// Param:
	//		force: A vec3 which sets Rigidbody m_velocity and m_angularvelocity
	//		pos: A vec3 which sets Rigidbody m_angularvelocity
	//----------------------------------------------------------------------------------------------
	void applyForce(glm::vec3 force, glm::vec3 pos);

	//void applyForceToActor(Rigidbody3D* actor2, glm::vec3 force);
	//virtual bool CheckCollision(PhysicsObject* pOther) = 0;

	//----------------------------------------------------------------------------------------------
	// Gets rigidbody m_postition
	//
	// Return:
	//		Returns a vec3 m_postition
	//----------------------------------------------------------------------------------------------
	glm::vec3 getPostition() { return m_postition; }
	//----------------------------------------------------------------------------------------------
	// Gets rigidbody m_rotation
	//
	// Return:
	//		Returns a mat4 m_rotation
	//----------------------------------------------------------------------------------------------
	glm::mat4 getRotation() { return m_rotation; }
	//----------------------------------------------------------------------------------------------
	// Gets rigidbody m_Rotation
	//
	// Return:
	//		Returns a float m_Rotation
	//----------------------------------------------------------------------------------------------
	float getrotation() { return m_Rotation; }
	//----------------------------------------------------------------------------------------------
	// Gets rigidbody m_velocity
	//
	// Return:
	//		Returns a vec3 m_velocity
	//----------------------------------------------------------------------------------------------
	glm::vec3 getVelocity() { return m_velocity; }
	//----------------------------------------------------------------------------------------------
	// Gets rigidbody m_mass
	//
	// Return:
	//		Returns a float m_mass
	//----------------------------------------------------------------------------------------------
	float getMass() { return m_mass; }
	//----------------------------------------------------------------------------------------------
	// sets rigidbody m_velocity
	//
	// Param:
	//		vel: A vec3 which sets rigidbody m_velocity
	//----------------------------------------------------------------------------------------------
	void setVelocity(glm::vec3 vel) { m_velocity = vel; }
	//----------------------------------------------------------------------------------------------
	// Gets rigidbody m_elasticity
	//
	// Return:
	//		Returns a float m_elasticity
	//----------------------------------------------------------------------------------------------
	float getElasticity() { return m_elasticity; }
	//----------------------------------------------------------------------------------------------
	// sets rigidbody m_postition
	//
	// Param:
	//		pos: A vec3 which sets rigidbody m_postition
	//----------------------------------------------------------------------------------------------
	void setPosition(glm::vec3 pos) { m_postition = pos; }
	//----------------------------------------------------------------------------------------------
	// Resolves the collision objects
	//
	// Param:
	//		actor2: A Rigidbody pointer to ther other shape
	//		contact: A vec3 of the contact point of the collision
	//		collisionormal: A vec3 pointer which is used to get the normal
	//----------------------------------------------------------------------------------------------
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

