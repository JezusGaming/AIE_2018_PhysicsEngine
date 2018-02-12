#include "Box.h"
#include <Gizmos.h>


Box::Box(glm::vec2 position, glm::vec2 velocity, float mass, float width, float hight, glm::vec4 colour) : Rigidbody(BOX, position, velocity, width, hight, mass)
{
}

Box::~Box()
{
}

void Box::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(m_postition, m_dimensions, m_colour);
}
