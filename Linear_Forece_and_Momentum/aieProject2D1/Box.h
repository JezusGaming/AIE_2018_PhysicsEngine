#pragma once
#include "Rigidbody.h"
class Box : public Rigidbody
{
protected:
	float m_width;
	float m_hight;
	glm::vec2 m_min;
	glm::vec2 m_max;
	glm::vec2 m_dimensions;
	glm::vec4 m_colour;
public:
	Box(glm::vec2 position, glm::vec2 velocity, float mass, float width, float hight, glm::vec4 colour);
	~Box();

	virtual void makeGizmo();

	float getWidth() { return m_width; }
	float getHight() { return m_hight; }
	glm::vec2 getMin() { return glm::vec2(m_postition.x - (m_width ), m_postition.y - (m_hight )); }
	glm::vec2 getMax() { return glm::vec2(m_postition.x + (m_width), m_postition.y + (m_hight)); }
	glm::vec2 getDimensions() { return m_dimensions; }
	glm::vec4 getColour() { return m_colour; }


};

