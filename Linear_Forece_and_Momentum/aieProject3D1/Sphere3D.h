#pragma once
#include "Rigidbody3D.h"
class Sphere3D : public Rigidbody3D
{
public:
	//----------------------------------------------------------------------------------------------
	// constructer initializes values
	//----------------------------------------------------------------------------------------------
	Sphere3D(glm::vec3 position, glm::vec3 velocity, float mass, float radius, glm::vec4 colour);
	//----------------------------------------------------------------------------------------------
	// constructer initializes values like the other but has an extra value speed
	//----------------------------------------------------------------------------------------------
	Sphere3D(glm::vec3 position, float inclination, float speed, float mass, float radius, glm::vec4 colour);
	//----------------------------------------------------------------------------------------------
	// defualt destructor
	//----------------------------------------------------------------------------------------------
	~Sphere3D();
	//----------------------------------------------------------------------------------------------
	// Makes a plane and draws it
	//----------------------------------------------------------------------------------------------
	virtual void makeGizmo();
	//virtual bool CheckCollision(PhysicsObject* pOther);
	//----------------------------------------------------------------------------------------------
	// Gets sphere m_radius
	//
	// Return:
	//		Returns a float m_radius
	//----------------------------------------------------------------------------------------------
	float getRadius() { return m_radius; }
	//----------------------------------------------------------------------------------------------
	// Gets sphere m_colour
	//
	// Return:
	//		Returns a vec4 m_colour
	//----------------------------------------------------------------------------------------------
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};

