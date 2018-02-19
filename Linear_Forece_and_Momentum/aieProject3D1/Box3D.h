#pragma once
#include "Rigidbody3D.h"
class Box3D : public Rigidbody3D
{
protected:
	float m_width;
	float m_hight;
	float m_depth;
	glm::vec3 m_min;
	glm::vec3 m_max;
	glm::vec3 m_dimensions;
	glm::vec4 m_colour;
public:
	Box3D(glm::vec3 position, glm::vec3 velocity, float mass, float width, float hight , float depth, glm::vec4 colour);
	~Box3D();

	virtual void makeGizmo();

	float getWidth() { return m_width; }
	float getHight() { return m_hight; }
	float getDepth() { return m_depth; }
	glm::vec3 getMin() { return glm::vec3(m_postition.x - (m_width), m_postition.y - (m_hight), m_postition.z - (m_depth)); }
	glm::vec3 getMax() { return glm::vec3(m_postition.x + (m_width), m_postition.y + (m_hight), m_postition.z + (m_depth)); }
	glm::vec3 getDimensions() { return m_dimensions; }
	glm::vec4 getColour() { return m_colour; }
};

