#include "Box3D.h"
#include <Gizmos.h>

Box3D::Box3D(glm::vec3 position, glm::vec3 velocity, float mass, float width, float hight, float depth, glm::vec4 colour) : Rigidbody3D(ShapeType::BOX, position, velocity, 0, mass)
{
	m_width = width;
	m_hight = hight;
	m_depth = depth;
	m_dimensions = glm::vec3(m_width, m_hight, m_depth);
	/*m_min = glm::vec2(position.x - (width * 0.5f), position.y - (hight * 0.5f));
	m_max = glm::vec2(position.x + (width * 0.5f), position.y + (hight * 0.5f));*/
	m_colour = colour;
	m_moment = 1.0f / 12.0f * mass * width * hight;
}

Box3D::~Box3D()
{
}

void Box3D::makeGizmo()
{
	aie::Gizmos::addAABBFilled(m_postition, m_dimensions, m_colour);
}

