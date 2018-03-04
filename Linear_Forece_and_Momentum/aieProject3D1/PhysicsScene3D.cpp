#include "PhysicsScene3D.h"
#include "PhysicsObject3D.h"
#include "Rigidbody3D.h"
#include <iostream>
#include <algorithm>
#include <list>
#include "Sphere3D.h"
#include "Plane3D.h"
#include "Box3D.h"
#include "BoxOOB.h"
typedef bool(*fn)(PhysicsObject3D*, PhysicsObject3D*);
//----------------------------------------------------------------------------------------------
//default constructer
//----------------------------------------------------------------------------------------------
PhysicsScene3D::PhysicsScene3D() : m_timeStep(0.01f), m_gravity(glm::vec3(0, 0, 0))
{

}
//----------------------------------------------------------------------------------------------
// defualt destructor
//----------------------------------------------------------------------------------------------
PhysicsScene3D::~PhysicsScene3D()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

static fn collisionFunctionArray[] =
{
	PhysicsScene3D::plane2Plane, PhysicsScene3D::plane2Sphere, PhysicsScene3D::plane2Box,
	PhysicsScene3D::sphere2Plane, PhysicsScene3D::sphere2Sphere, PhysicsScene3D::sphere2Box,
	/*PhysicsScene3D::AABB2Plane, PhysicsScene3D::AABB2Sphere, PhysicsScene3D::AABB2AABB,*/
	PhysicsScene3D::Box2Box, PhysicsScene3D::Box2Sphere, PhysicsScene3D::Box2Plane
};
//----------------------------------------------------------------------------------------------
// Checks for collision iterats through shapes calls a funtionptr which calls one of the many 
// collision functions based on the shapes
//----------------------------------------------------------------------------------------------
void PhysicsScene3D::checkForCollision()
{
	int actorCount = m_actors.size();

	// need to check for collisions against all objects except this one.
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject3D* object1 = m_actors[outer];
			PhysicsObject3D* object2 = m_actors[inner];
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();

			// using function pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				// did a collision occur
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}
//----------------------------------------------------------------------------------------------
// Checks for collision between two planes
//
// Param:
//		obj1: A physicsObject pointer used to help resolve the collision
//		obj2: Another physicsObject pointer used to help resolve the collision
// Return:
//		Returns false because we will not need to check is two planes collide
//----------------------------------------------------------------------------------------------
bool PhysicsScene3D::plane2Plane(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	return false;
}
//----------------------------------------------------------------------------------------------
// Checks for collision between plane2Sphere
//
// Param:
//		obj1: A physicsObject pointer used to help resolve the collision
//		obj2: Another physicsObject pointer used to help resolve the collision
// Return:
//		Returns sphere2Plane which resolves the collision if there is any
//----------------------------------------------------------------------------------------------
bool PhysicsScene3D::plane2Sphere(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	return sphere2Plane(obj2, obj1);
}
//----------------------------------------------------------------------------------------------
// Checks for collision between plane2Box
//
// Param:
//		obj1: A physicsObject pointer used to help resolve the collision
//		obj2: Another physicsObject pointer used to help resolve the collision
// Return:
//		Returns box2Plane which resolves the collision if there is any
//----------------------------------------------------------------------------------------------
bool PhysicsScene3D::plane2Box(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	return Box2Plane(obj2, obj1);
}

//bool PhysicsScene3D::plane2AABB(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
//{
//	return AABB2Plane(obj2, obj1);
//}

//----------------------------------------------------------------------------------------------
// Checks for collision between sphere2Plane
//
// Param:
//		obj1: A physicsObject pointer used to help resolve the collision
//		obj2: Another physicsObject pointer used to help resolve the collision
// Return:
//		Returns true if there is a collision but resolves it before returning true, if there is
//		no collision then returns false
//----------------------------------------------------------------------------------------------
bool PhysicsScene3D::sphere2Plane(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	Sphere3D *sphere = dynamic_cast<Sphere3D*>(obj1);
	Plane3D *plane = dynamic_cast<Plane3D*>(obj2);

	// if we are successful then test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec3 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(sphere->getPostition(), plane->getNormal()) - plane->getDistance();

		// if we are behind plane then we flip the normal
		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->getRadius() - sphereToPlane;
		if (intersection > 0)
		{
			glm::vec3 contact = sphere->getPostition() + (collisionNormal * -sphere->getRadius());
			plane->resolveCollision(sphere, contact);
			//sphere->setVelocity(glm::vec2(0, 0));

			sphere->setPosition(contact + collisionNormal * sphere->getRadius() + intersection);

			return true;
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------
// Checks for collision between sphere2Sphere
//
// Param:
//		obj1: A physicsObject pointer used to help resolve the collision
//		obj2: Another physicsObject pointer used to help resolve the collision
// Return:
//		Returns true if there is a collision but resolves it before returning true, if there is
//		no collision then returns false
//----------------------------------------------------------------------------------------------
bool PhysicsScene3D::sphere2Sphere(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	// try to case objects to sphere and sphere
	Sphere3D *sphere1 = dynamic_cast<Sphere3D*>(obj1);
	Sphere3D *sphere2 = dynamic_cast<Sphere3D*>(obj2);
	// if we are successful then test for collision
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		glm::vec3 delta = sphere2->getPostition() - sphere1->getPostition();
		float distance = glm::length(delta);
		float intersection = sphere1->getRadius() + sphere2->getRadius() - distance;

		if (intersection > 0)
		{
			glm::vec3 contactForce = 0.5f * (distance - (sphere1->getRadius() + sphere2->getRadius())) * delta / distance;

			sphere1->setPosition(sphere1->getPostition() + contactForce);
			sphere2->setPosition(sphere2->getPostition() - contactForce);

			sphere1->resolveCollision(sphere2, 0.05f * (sphere1->getPostition() + sphere2->getPostition()));
			//sphere1->setVelocity(glm::vec2(0, 0));
			//sphere2->setVelocity(glm::vec2(0, 0));
			return true;
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------
// Checks for collision between sphere2Box
//
// Param:
//		obj1: A physicsObject pointer used to help resolve the collision
//		obj2: Another physicsObject pointer used to help resolve the collision
// Return:
//		Returns box2Sphere which resolves the collision if there is any
//----------------------------------------------------------------------------------------------
bool PhysicsScene3D::sphere2Box(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	return Box2Sphere(obj2, obj1);
}

//bool PhysicsScene3D::sphere2AABB(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
//{
//	Sphere3D *sphere1 = dynamic_cast<Sphere3D*>(obj1);
//	Box3D *box1 = dynamic_cast<Box3D*>(obj2);
//
//	if (box1 != nullptr && sphere1 != nullptr)
//	{
//		glm::vec3 A = glm::clamp(sphere1->getPostition(), box1->getMin(), box1->getMax());
//		glm::vec3 V = A - sphere1->getPostition();
//
//		if (glm::length(V) <= sphere1->getRadius())
//		{
//			//sphere1->resolveCollision(box1);
//		}
//	}
//	return false;
//}

//bool PhysicsScene3D::AABB2Plane(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
//{
//	Box3D *box = dynamic_cast<Box3D*>(obj1);
//	Plane3D *plane = dynamic_cast<Plane3D*>(obj2);
//
//	if (box != nullptr && plane != nullptr)
//	{
//		glm::vec3 v = plane->getNormal();
//		glm::vec3 bottomLeft = box->getMin();
//		glm::vec3 bottomRight = box->getMin() + glm::vec3(box->getWidth(), 0, 0);
//		glm::vec3 topLeft = box->getMin() + glm::vec3(0, box->getHight() , 0);
//		glm::vec3 topRight = box->getMax() + glm::vec3(box->getWidth(), box->getHight(), box->getDepth());
//
//		if (glm::dot(v, bottomLeft) - plane->getDistance() < 0 ||
//			glm::dot(v, bottomRight) - plane->getDistance() < 0 ||
//			glm::dot(v, topLeft) - plane->getDistance() < 0 ||
//			glm::dot(v, topLeft) - plane->getDistance() < 0)
//		{
//			//plane->resolveCollision(box);
//			return true;
//		}
//	}
//
//	return false;
//}

//bool PhysicsScene3D::AABB2Sphere(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
//{
//	return sphere2AABB(obj2, obj1);
//}
//
//bool PhysicsScene3D::AABB2AABB(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
//{
//	Box3D *box1 = dynamic_cast<Box3D*>(obj1);
//	Box3D *box2 = dynamic_cast<Box3D*>(obj2);
//
//	if (box1 != nullptr && box2 != nullptr)
//	{
//		glm::vec3 max1 = box1->getMax();
//		glm::vec3 min1 = box1->getMin();
//		glm::vec3 max2 = box2->getMax();
//		glm::vec3 min2 = box2->getMin();
//
//		if (min1.x <= max2.x &&
//			min1.y <= max2.y &&
//			max1.x >= min2.x &&
//			max1.y >= min2.y)
//		{
//			//box1->resolveCollision(box2);
//			return true;
//		}
//	}
//	return false;
//}

//----------------------------------------------------------------------------------------------
// Checks for collision between Box2Box
//
// Param:
//		obj1: A physicsObject pointer used to help resolve the collision
//		obj2: Another physicsObject pointer used to help resolve the collision
// Return:
//		Returns true if there is a collision but resolves it before returning true, if there is
//		no collision then returns false
//----------------------------------------------------------------------------------------------
bool PhysicsScene3D::Box2Box(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	BoxOOB *box1 = dynamic_cast<BoxOOB*>(obj1);
	BoxOOB *box2 = dynamic_cast<BoxOOB*>(obj2);

	if (box1 != nullptr && box2 != nullptr) {
		glm::vec3 boxPos = box2->getPostition() - box1->getPostition();

		glm::vec3 norm(0, 0, 0);
		glm::vec3 contactForce1, contactForce2;
		glm::vec3 contact(0, 0, 0);
		float pen = 0;
		int numContacts = 0;

		box1->checkBoxCorners(*box2, contact, numContacts, norm, contactForce1);

		if (box2->checkBoxCorners(*box1, contact, numContacts, norm, contactForce2))
		{
			norm = -norm;
		}
		if (numContacts > 0)
		{
			glm::vec3 contactForce = 0.5f*(contactForce1 - contactForce2);
			box1->setPosition(box1->getPostition() - contactForce);
			box2->setPosition(box2->getPostition() + contactForce);
			box1->resolveCollision(box2, contact / float(numContacts), &norm);
			return true;
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------
// Checks for collision between Box2Box
//
// Param:
//		obj1: A physicsObject pointer used to help resolve the collision
//		obj2: Another physicsObject pointer used to help resolve the collision
// Return:
//		Returns true if there is a collision but resolves it before returning true, if there is
//		no collision then returns false
//----------------------------------------------------------------------------------------------
bool PhysicsScene3D::Box2Sphere(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	BoxOOB* box = dynamic_cast<BoxOOB*>(obj1);
	Sphere3D* sphere = dynamic_cast<Sphere3D*>(obj2);

	if (box != nullptr && sphere != nullptr)
	{
		glm::vec3 circlePos = sphere->getPostition() - box->getPostition();
		float w3 = box->getWidth() / 2, h3 = box->getHight() / 2, d3 = box->getDepth() / 2;

		int numContacts = 0;
		glm::vec3 contact(0, 0, 0); // contact is in our box coordinates

		// check the four corners to see if any of them are inside the circle
		for (float x = -w3; x <= w3; x += box->getWidth()) {
			for (float y = -h3; y <= h3; y += box->getHight()) {
				for (float z = -d3; z <= d3; z += box->getDepth()) {
					glm::vec3 p = x * box->getLocalX() + y * box->getLocalY() + z * box->getLocalZ();
					glm::vec3 dp = p - circlePos;
					if (dp.x*dp.x + dp.y*dp.y + dp.z*dp.z < sphere->getRadius()*sphere->getRadius())
					{
						numContacts++;
						contact += glm::vec3(x, y, z);
					}
				}
			}
		}
		glm::vec3* direction = nullptr;
		// get the local position of the circle centre
		glm::vec3 localPos(glm::dot(box->getLocalX(), circlePos),
			glm::dot(box->getLocalY(), circlePos),
			glm::dot(box->getLocalZ(), circlePos));
		if (localPos.y < h3 && localPos.y > -h3) {
			if (localPos.x > 0 && localPos.x < w3 + sphere->getRadius()) {
				numContacts++;
				contact += glm::vec3(w3, localPos.y, localPos.z);
				direction = new glm::vec3(box->getLocalX());
			}
			if (localPos.x < 0 && localPos.x > -(w3 + sphere->getRadius())) {
				numContacts++;
				contact += glm::vec3(-w3, localPos.y, localPos.z);
				direction = new glm::vec3(-box->getLocalX());
			}
			if (localPos.z > 0 && localPos.z < w3 + sphere->getRadius()) {
				numContacts++;
				contact += glm::vec3(w3, localPos.y, localPos.z);
				direction = new glm::vec3(box->getLocalX());
			}
			if (localPos.z < 0 && localPos.z > -(w3 + sphere->getRadius())) {
				numContacts++;
				contact += glm::vec3(-w3, localPos.y, localPos.z);
				direction = new glm::vec3(-box->getLocalX());
			}
		}
		if (localPos.x < w3 && localPos.x > -w3) {
			if (localPos.y > 0 && localPos.y < h3 + sphere->getRadius())
			{
				numContacts++;
				contact += glm::vec3(localPos.x, h3, localPos.z);
				direction = new glm::vec3(box->getLocalY());
			}
			if (localPos.y < 0 && localPos.y > -(h3 + sphere->getRadius()))
			{
				numContacts++;
				contact += glm::vec3(localPos.x, -h3, localPos.z);
				direction = new glm::vec3(-box->getLocalY());
			}
			if (localPos.z > 0 && localPos.z < h3 + sphere->getRadius())
			{
				numContacts++;
				contact += glm::vec3(localPos.x, h3, localPos.z);
				direction = new glm::vec3(box->getLocalY());
			}
			if (localPos.z < 0 && localPos.z > -(h3 + sphere->getRadius()))
			{
				numContacts++;
				contact += glm::vec3(localPos.x, -h3, localPos.z);
				direction = new glm::vec3(-box->getLocalY());
			}
		}
		if (localPos.z < d3 && localPos.z > -d3) {
			if (localPos.x > 0 && localPos.x < d3 + sphere->getRadius())
			{
				numContacts++;
				contact += glm::vec3(localPos.x, localPos.y, d3);
				direction = new glm::vec3(box->getLocalZ());
			}
			if (localPos.x < 0 && localPos.x > -(d3 + sphere->getRadius()))
			{
				numContacts++;
				contact += glm::vec3(localPos.x, localPos.y, -d3);
				direction = new glm::vec3(-box->getLocalY());
			}
			if (localPos.y > 0 && localPos.y < d3 + sphere->getRadius())
			{
				numContacts++;
				contact += glm::vec3(localPos.x, localPos.y, d3);
				direction = new glm::vec3(box->getLocalZ());
			}
			if (localPos.y < 0 && localPos.y > -(d3 + sphere->getRadius()))
			{
				numContacts++;
				contact += glm::vec3(localPos.x, localPos.y, -d3);
				direction = new glm::vec3(-box->getLocalY());
			}
		}
		if (numContacts > 0)
		{
			// average, and convert back into world coords
			contact = box->getPostition() + (1.0f / numContacts) * (box->getLocalX() * contact.x + box->getLocalY() * contact.y + box->getLocalZ() * contact.z);
			box->resolveCollision(sphere, contact, direction);
		}
		delete direction;
	}
	return false;
}
//----------------------------------------------------------------------------------------------
// Checks for collision between Box2Box
//
// Param:
//		obj1: A physicsObject pointer used to help resolve the collision
//		obj2: Another physicsObject pointer used to help resolve the collision
// Return:
//		Returns true if there is a collision but resolves it before returning true, if there is
//		no collision then returns false
//----------------------------------------------------------------------------------------------
bool PhysicsScene3D::Box2Plane(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	BoxOOB *box = dynamic_cast<BoxOOB*>(obj1);
	Plane3D *plane = dynamic_cast<Plane3D*>(obj2);

	//if we are successful then test for collision
	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		glm::vec3 contact(0, 0, 0);
		float contactV = 0;
		float radius = 0.5f * fminf(box->getWidth(), box->getHight());
		float penetration = 0;

		// which side is the centre of mass on?
		glm::vec3 planeOrigin = plane->getNormal() * plane->getDistance();
		float comFromPlane = glm::dot(box->getPostition() - planeOrigin, plane->getNormal());

		// check all four corners to see if we've hit the plane
		for (float x = -box->getExtents().x; x < box->getWidth(); x += box->getWidth())
		{
			for (float y = -box->getExtents().y; y < box->getHight(); y += box->getHight())
			{
				for (float z = -box->getExtents().z; z < box->getDepth(); z += box->getDepth())
				{
					// get the position of the corner in world space
					glm::vec3 p = box->getPostition() + x * box->getLocalX() + y * box->getLocalY() + z * box->getLocalZ();

					float distFromPlane = glm::dot(p - planeOrigin, plane->getNormal());

					// this is the total velocity of the point
					float velocityIntoPlane = glm::dot(box->getVelocity() + box->getrotation() * (-y * box->getLocalX() + x * box->getLocalY() + z * box->getLocalZ()), plane->getNormal());

					// if this corner is on the opposite side from the COM,
					// and moving further in, we need to resolve the collision
					if ((distFromPlane > 0 && comFromPlane < 0 && velocityIntoPlane > 0) ||
						(distFromPlane < 0 && comFromPlane > 0 && velocityIntoPlane > 0)) 
					{
						numContacts++;
						contact += p;
						contactV += velocityIntoPlane;
						if (comFromPlane >= 0)
						{
							if (penetration > distFromPlane)
								penetration = distFromPlane;
						}
						else {
							if (penetration < distFromPlane)
								penetration = distFromPlane;
						}
					}
				}
			}
		}
		// we've had a hit - typically only two corners can contact
		if (numContacts > 0)
		{
			// get the average collision velocity into the plane
			// (covers linear and rotational velocity of all corners involved)
			float collisionV = contactV / (float)numContacts;

			// get the acceleration required to stop (restitution = 0) or reverse
			// (restitution = 1) the average velocity into the plane
			glm::vec3 acceleration = -plane->getNormal() * ((1.0f + box->getElasticity()) * collisionV);
			// and the average position at which we'll apply the force
			// (corner or edge centre)
			glm::vec3 localContact = (contact / (float)numContacts) - box->getPostition();
			// this is the perpendicular distance we apply the force at relative to
			// the COM, so Torque = F*r
			float r = glm::dot(localContact, glm::vec3(plane->getNormal().y, -plane->getNormal().x, plane->getNormal().z));

			// work out the "effective mass" - this is a combination of moment of
			// inertia and mass, and tells us how much the contact point velocity
			// will change with the force we're applying
			float mass0 = 1.0f / (1.0f / box->getMass() + (r*r) / box->getMoment());
			// and apply the force
			box->applyForce(acceleration * mass0, localContact);

			box->setPosition(box->getPostition() - plane->getNormal() * penetration);
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------
// Adds an actor from the actor array in the physicsScene
//
// Param:
//		actor: A physicsObject pointer which gets added to the actor array
//----------------------------------------------------------------------------------------------
void PhysicsScene3D::addActor(PhysicsObject3D * actor)
{
	m_actors.push_back(actor);
}
//----------------------------------------------------------------------------------------------
// Removes an actor from the actor array in the physicsScene
//
// Param:
//		actor: A physicsObject pointer which gets remove from the scene
//----------------------------------------------------------------------------------------------
void PhysicsScene3D::removeActor(PhysicsObject3D* actor)
{
	delete m_actors.back();
	m_actors.pop_back();
}
//----------------------------------------------------------------------------------------------
// Updates actors and checks for collision
//
// Param:
//		dt: A float which represents deltatime which increases over time
//----------------------------------------------------------------------------------------------
void PhysicsScene3D::update(float dt)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
				pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
	}
	checkForCollision();
}
//----------------------------------------------------------------------------------------------
// Updates each actors gizmos every frame
//----------------------------------------------------------------------------------------------
void PhysicsScene3D::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}
//----------------------------------------------------------------------------------------------
// Used only for debug purpose
//----------------------------------------------------------------------------------------------
void PhysicsScene3D::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
		std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}
