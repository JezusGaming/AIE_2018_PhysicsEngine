#pragma once
#include "Rigidbody3D.h"
class BoxOOB : public Rigidbody3D
{
public:
	BoxOOB(glm::vec3 position, glm::vec3 velocity, float mass, float width, float hight, float depth, glm::vec4 colour);
	~BoxOOB();

	void fixedUpdate(glm::vec3 gravity, float timeStep);
	void makeGizmo();
	bool checkBoxCorners(BoxOOB& box, glm::vec3& contact, int& numContacts, glm::vec3& edgeNormal, glm::vec3& contactForce);

	float getWidth() { return m_width; }
	float getHight() { return m_hight; }
	float getDepth() { return m_depth; }
	float getMoment() { return m_moment; }
	glm::vec3 getMin() { return glm::vec3(m_postition.x - (m_width), m_postition.y - (m_hight), m_postition.z - (m_depth)); }
	glm::vec3 getMax() { return glm::vec3(m_postition.x + (m_width), m_postition.y + (m_hight), m_postition.z + (m_depth)); }
	glm::vec3 getExtents() { return m_extents; }
	glm::vec3 getLocalX() { return m_localX; }
	glm::vec3 getLocalY() { return m_localY; }
	glm::vec3 getLocalZ() { return m_localZ; }
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
	//glm::vec3 m_dimensions;
};

