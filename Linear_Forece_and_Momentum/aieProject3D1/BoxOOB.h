#pragma once
#include "Rigidbody3D.h"
class BoxOOB : public Rigidbody3D
{
public:
	//----------------------------------------------------------------------------------------------
	// constructer initializes values
	//----------------------------------------------------------------------------------------------
	BoxOOB(glm::vec3 position, glm::vec3 velocity, float mass, float width, float hight, float depth, glm::vec4 colour);
	//----------------------------------------------------------------------------------------------
	// defualt destructor
	//----------------------------------------------------------------------------------------------
	~BoxOOB();
	//----------------------------------------------------------------------------------------------
	// Updates the BoxOOB and rigidbody every frame
	//
	// Param:
	//		gravity: A vec3 which sets BoxOOB m_gravity to help apply velocity to objects
	//		timeStep: A float which sets BoxOOB m_timeStep to help apply velocity to objects ect
	//----------------------------------------------------------------------------------------------
	void fixedUpdate(glm::vec3 gravity, float timeStep);
	//----------------------------------------------------------------------------------------------
	// Makes a BoxOOB and draws it
	//----------------------------------------------------------------------------------------------
	void makeGizmo();

	bool checkBoxCorners(BoxOOB& box, glm::vec3& contact, int& numContacts, glm::vec3& edgeNormal, glm::vec3& contactForce);
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB m_width
	//
	// Return:
	//		Returns a float m_width
	//----------------------------------------------------------------------------------------------
	float getWidth() { return m_width; }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB m_hight
	//
	// Return:
	//		Returns a float m_hight
	//----------------------------------------------------------------------------------------------
	float getHight() { return m_hight; }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB m_depth
	//
	// Return:
	//		Returns a float m_depth
	//----------------------------------------------------------------------------------------------
	float getDepth() { return m_depth; }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB m_moment
	//
	// Return:
	//		Returns a float m_moment
	//----------------------------------------------------------------------------------------------
	float getMoment() { return m_moment; }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB Min points
	//
	// Return:
	//		Returns a vec3 of th box min
	//----------------------------------------------------------------------------------------------
	glm::vec3 getMin() { return glm::vec3(m_postition.x - (m_width), m_postition.y - (m_hight), m_postition.z - (m_depth)); }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB Max points
	//
	// Return:
	//		Returns a vec3 of th box max
	//----------------------------------------------------------------------------------------------
	glm::vec3 getMax() { return glm::vec3(m_postition.x + (m_width), m_postition.y + (m_hight), m_postition.z + (m_depth)); }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB m_extents
	//
	// Return:
	//		Returns a vec3 m_extents
	//----------------------------------------------------------------------------------------------
	glm::vec3 getExtents() { return m_extents; }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB m_localX
	//
	// Return:
	//		Returns a vec3 m_localX
	//----------------------------------------------------------------------------------------------
	glm::vec3 getLocalX() { return m_localX; }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB m_localY
	//
	// Return:
	//		Returns a vec3 m_localY
	//----------------------------------------------------------------------------------------------
	glm::vec3 getLocalY() { return m_localY; }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB m_localZ
	//
	// Return:
	//		Returns a vec3 m_localZ
	//----------------------------------------------------------------------------------------------
	glm::vec3 getLocalZ() { return m_localZ; }
	//----------------------------------------------------------------------------------------------
	// Gets BoxOOB m_colour
	//
	// Return:
	//		Returns a vec4 m_colour
	//----------------------------------------------------------------------------------------------
	glm::vec4 getColour() { return m_colour; }

protected:
	glm::vec3 m_extents;
	glm::vec4 m_colour;

	glm::vec3 m_localX;
	glm::vec3 m_localY;
	glm::vec3 m_localZ;

	float m_width;
	float m_hight;
	float m_depth;
	glm::vec3 m_min;
	glm::vec3 m_max;
};

