#include "BoxOOB.h"
#include <Gizmos.h>


BoxOOB::BoxOOB(glm::vec3 position, glm::vec3 velocity, float mass, float width, float hight, float depth, glm::vec4 colour) : Rigidbody3D(ShapeType::BOX, position, velocity, 0, mass)
{
	m_width = width;
	m_hight = hight;
	m_depth = depth;
	//m_dimensions = glm::vec3(m_width, m_hight, m_depth);
	m_extents = glm::vec3(m_width, m_hight, m_depth);
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
	float cs = cosf(m_Rotation);
	float sn = sinf(m_Rotation);
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
	//aie::Gizmos::addTri(p1, p2, p4, m_colour);
	//aie::Gizmos::addTri(p1, p4, p3, m_colour);

	glm::mat4 transform = glm::mat4(1);
		transform[0] = glm::vec4(m_localX, 0);
		transform[1] = glm::vec4(m_localY, 0);
		transform[2] = glm::vec4(m_localZ, 0);
	aie::Gizmos::addAABBFilled(m_postition, m_extents, m_colour,&transform);
}

bool BoxOOB::checkBoxCorners(BoxOOB& box, glm::vec3& contact, int& numContacts, glm::vec3& edgeNormal, glm::vec3& contactForce)
{
	float minX, maxX, minY, maxY, minZ, maxZ;
	float boxW = box.getExtents().x * 2;
	float boxH = box.getExtents().y * 2;
	float boxZ = box.getExtents().z * 2;
	float penetration = 0;

	bool first = true;
	for (float x = -box.getExtents().x; x < boxW; x += boxW)
	{
		for (float y = -box.getExtents().y; y < boxH; y += boxH)
		{
			for (float z = -box.getExtents().z; z < boxZ; z += boxZ)
			{
				// position in worldspace
				glm::vec3 p = box.getPostition() + x * box.m_localX + y * box.m_localY + z * box.m_localZ;
				// position in our box's space
				glm::vec3 p0(glm::dot(p - m_postition, m_localX), glm::dot(p - m_postition, m_localY), glm::dot(p - m_postition, m_localZ));

				float w3 = m_extents.x, h3 = m_extents.y, z3 = m_extents.z;
				if (p0.y < h3 && p0.y > -h3)
				{
					if (p0.x > 0 && p0.x < w3)
					{
						numContacts++;
						contact += m_postition + w3 * m_localX + p0.y * m_localY + p0.z * m_localZ;
						edgeNormal = m_localX; 
						penetration = w3 - p0.x;
					}
					if (p0.x < 0 && p0.x > -w3)
					{
						numContacts++;
						contact += m_postition - w3 * m_localX + p0.y * m_localY + p0.z * m_localZ;
						edgeNormal = -m_localX;
						penetration = w3 - p0.x;
					}
					if (p0.z > 0 && p0.z < z3)
					{
						numContacts++;
						contact += m_postition + w3 * m_localX + p0.y * m_localY + p0.z * m_localZ;
						edgeNormal = m_localX;
						penetration = z3 - p0.z;
					}
					if (p0.z < 0 && p0.z > -z3)
					{
						numContacts++;
						contact += m_postition + w3 * m_localX + p0.y * m_localY - p0.z * m_localZ;
						edgeNormal = -m_localZ;
						penetration = z3 - p0.z;
					}
				}
				if (p0.x < w3 && p0.x > -w3)
				{
					if (p0.y > 0 && p0.y < h3)
					{
						numContacts++;
						contact += m_postition + p0.x * m_localX + h3 * m_localY + p0.z * m_localZ;
						float pen0 = h3 - p0.y;
						if (pen0 < penetration || penetration == 0) {
							penetration = pen0;
							edgeNormal = m_localY;
						}
					}
					if (p0.y < 0 && p0.y > -h3)
					{
						numContacts++;
						contact += m_postition + p0.x * m_localX - h3 * m_localY + p0.z * m_localZ;
						float pen0 = h3 + p0.y;
						if (pen0 < penetration || penetration == 0) {
							penetration = pen0;
							edgeNormal = -m_localY;
						}
					}
					if (p0.z > 0 && p0.z < z3)
					{
						numContacts++;
						contact += m_postition + p0.x * m_localX + h3 * m_localY + p0.z * m_localZ;
						edgeNormal = m_localZ;
						penetration = z3 - p0.z;
					}
					if (p0.z < 0 && p0.z > -z3)
					{
						numContacts++;
						contact += m_postition - p0.x * m_localX + h3 * m_localY - p0.z * m_localZ;
						edgeNormal = -m_localZ;
						penetration = z3 - p0.z;
					}
				}
				if (p0.z < z3 && p0.z > -z3)
				{
					if (p0.x > 0 && p0.x < w3)
					{
						numContacts++;
						contact += m_postition + p0.x * m_localX + p0.y * m_localY + z3 * m_localZ;
						edgeNormal = m_localX;
						penetration = w3 - p0.x;
					}
					if (p0.x < 0 && p0.x > -w3)
					{
						numContacts++;
						contact += m_postition - p0.x * m_localX + p0.y * m_localY + z3 * m_localZ;
						edgeNormal = -m_localX;
						penetration = w3 - p0.x;
					}
					if (p0.y > 0 && p0.y < h3)
					{
						numContacts++;
						contact += m_postition + p0.x * m_localX + p0.y * m_localY + z3 * m_localZ;
						float pen0 = h3 - p0.y;
						if (pen0 < penetration || penetration == 0) {
							penetration = pen0;
							edgeNormal = m_localY;
						}
					}
					if (p0.y < 0 && p0.y > -h3)
					{
						numContacts++;
						contact += m_postition + p0.x * m_localX - p0.y * m_localY + z3 * m_localZ;
						float pen0 = h3 + p0.y;
						if (pen0 < penetration || penetration == 0) {
							penetration = pen0;
							edgeNormal = -m_localY;
						}
					}
				}
			}
		}
		/*if (maxX <-m_extents.x || minX >m_extents.x ||
			maxY<-m_extents.y || minY >m_extents.y ||
			maxZ<-m_extents.z || minZ >m_extents.z)
			return false;
		if (numLocalContact == 0)
			return false;

		bool res = false;

		contact += m_postition + (localContact.x*m_localX + localContact.y*m_localY + localContact * m_localZ) / (float)numLocalContact;
		numContacts++;

		float pen0 = m_extents.x - minX;
		if (pen0 > 0 && (pen0 < pen || pen == 0))
		{
			edgeNormal = m_localX;
			pen = pen0;
			res = true;
		}
		pen0 = maxX + m_extents.x;
		if (pen0 > 0 && (pen0 < pen || pen == 0)) 
		{
			edgeNormal = -m_localX;
			pen = pen0;
			res = true;
		}
		pen0 = m_extents.y - minY;
		if (pen0 > 0 && (pen0 < pen || pen == 0)) 
		{
			edgeNormal = m_localY;
			pen = pen0;
			res = true;
		}
		pen0 = maxY + m_extents.y;
		if (pen0 > 0 && (pen0 < pen || pen == 0)) 
		{
			edgeNormal = -m_localY;
			pen = pen0;
			res = true;
		}
		pen0 = m_extents.z - minZ;
		if (pen0 > 0 && (pen0 < pen || pen == 0))
		{
			edgeNormal = m_localZ;
			pen = pen0;
			res = true;
		}
		pen0 = maxZ + m_extents.z;
		if (pen0 > 0 && (pen0 < pen || pen == 0))
		{
			edgeNormal = -m_localZ;
			pen = pen0;
			res = true;
		}
		return res;*/

	}
	contact = penetration * edgeNormal;
	return (penetration != 0);
}