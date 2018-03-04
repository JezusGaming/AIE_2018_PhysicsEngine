#pragma once
#include "PhysicsObject3D.h"
#include "Rigidbody3D.h"
class Plane3D : public PhysicsObject3D
{
public:
	//----------------------------------------------------------------------------------------------
	// constructer initializes values
	//----------------------------------------------------------------------------------------------
	Plane3D(glm::vec3 normal, float distance);
	//----------------------------------------------------------------------------------------------
	// defualt destructor
	//----------------------------------------------------------------------------------------------
	~Plane3D();
	virtual void fixedUpdate(glm::vec3 gravity, float timeStep);
	//----------------------------------------------------------------------------------------------
	// Used only for debug purpose
	//----------------------------------------------------------------------------------------------
	virtual void debug() {}
	//----------------------------------------------------------------------------------------------
	// Makes a plane and draws it, work in progress 
	//----------------------------------------------------------------------------------------------
	virtual void makeGizmo();
	virtual void resetPosition();
	//----------------------------------------------------------------------------------------------
	// Gets the planes m_normal
	//
	// Return:
	//		Returns a vec3 m_normal
	//----------------------------------------------------------------------------------------------
	glm::vec3 getNormal() { return m_normal; }
	//----------------------------------------------------------------------------------------------
	// Gets the planes m_distanceToOrigin
	//
	// Return:
	//		Returns a vec3 m_distanceToOrigin
	//----------------------------------------------------------------------------------------------
	float getDistance() { return m_distanceToOrigin; }
	//----------------------------------------------------------------------------------------------
	// Resolves the collision of a plane and other shapes
	//
	// Param:
	//		actor: A Rigidbody pointer to ther other shape
	//		contact: A vec3 of the contact point of the collision
	//----------------------------------------------------------------------------------------------
	void resolveCollision(Rigidbody3D* actor2, glm::vec3 contact);

protected:
	glm::vec3 m_normal;
	float m_distanceToOrigin;
};

