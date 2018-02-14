#include "Box.h"
#include <Gizmos.h>

Box::Box(glm::vec2 position, glm::vec2 velocity, float mass, float width, float hight, glm::vec4 colour) : Rigidbody(ShapeType::BOX, position, velocity, 0, mass, 0.2f, 0.2f, 0.8f)
{
	m_width = width;
	m_hight = hight;

	m_dimensions = glm::vec2(m_width, m_hight);
	/*m_min = glm::vec2(position.x - (width * 0.5f), position.y - (hight * 0.5f));
	m_max = glm::vec2(position.x + (width * 0.5f), position.y + (hight * 0.5f));*/

	m_colour = colour;
}

Box::~Box()
{
}

void Box::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(m_postition, m_dimensions, m_colour);
}
