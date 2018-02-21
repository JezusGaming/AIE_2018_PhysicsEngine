#include "BoxOOB.h"
#include <Gizmos.h>


BoxOOB::BoxOOB(glm::vec3 position, glm::vec3 velocity, float mass, float width, float hight, float depth, glm::vec4 colour) : Rigidbody3D(ShapeType::BOX, position, velocity, 0, mass)
{
	m_width = width;
	m_hight = hight;
	m_depth = depth;
	m_dimensions = glm::vec3(m_width, m_hight, m_depth);
	m_colour = colour;
	m_moment = 1.0f / 12.0f * mass * width * hight;
}


BoxOOB::~BoxOOB()
{
}

void BoxOOB::fixedUpdate(glm::vec3 gravity, float timeStep)
{
	Rigidbody3D::fixedUpdate(gravity, timeStep);

	//store the local axes
	float cs = cosf(m_rotation);
	float sn = sinf(m_rotation);
	m_localX = glm::normalize(glm::vec3(cs, sn, -sn));
	m_localY = glm::normalize(glm::vec3(-sn, cs, sn));
	m_localZ = glm::normalize(glm::vec3( sn, -sn, cs));
}

void BoxOOB::makeGizmo()
{
	// if only using rotation 
	// glm::mat4 transform = glm::rotate(m_rotation, glm::vec3(0, 0, 1)); 
	// aie::Gizmos::add2DAABBFilled(getCenter(), 
	// m_extents, m_colour, &transform); 

	// draw using local axes
	glm::vec3 p1 = m_postition - m_localX * m_extents.x - m_localY * m_extents.y - m_localZ * m_extents.z;
	glm::vec3 p2 = m_postition + m_localX * m_extents.x - m_localY * m_extents.y - m_localZ * m_extents.z;
	glm::vec3 p3 = m_postition - m_localX * m_extents.x + m_localY * m_extents.y + m_localZ * m_extents.z;
	glm::vec3 p4 = m_postition + m_localX * m_extents.x + m_localY * m_extents.y + m_localZ * m_extents.z;
	aie::Gizmos::addTri(p1, p2, p4, m_colour);
	aie::Gizmos::addTri(p1, p4, p3, m_colour);
}
