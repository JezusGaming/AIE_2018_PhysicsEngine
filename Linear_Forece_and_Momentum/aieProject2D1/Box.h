#pragma once
#include "Rigidbody.h"
class Box : public Rigidbody
{
public:
	Box(glm::vec2 position, glm::vec2 velocity, float mass, float width, float hight, glm::vec4 colour);
	~Box();

	virtual void makeGizmo();

	glm::vec2 getDimensions() { return m_dimensions; }
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_width;
	float m_hight;

	glm::vec2 m_dimensions;
	glm::vec4 m_colour;
};

