#include "PhysicsScene3D.h"
#include "PhysicsObject3D.h"
#include "Rigidbody3D.h"
#include <iostream>
#include <algorithm>
#include <list>
#include "Sphere3D.h"
#include "Plane3D.h"
#include "Box3D.h"
typedef bool(*fn)(PhysicsObject3D*, PhysicsObject3D*);

PhysicsScene3D::PhysicsScene3D() : m_timeStep(0.01f), m_gravity(glm::vec3(0, 0, 0))
{

}

PhysicsScene3D::~PhysicsScene3D()
{
	for (auto pActor : m_actors)
	{
		pActor;
	}
}

static fn collisionFunctionArray[] =
{
	PhysicsScene3D::plane2Plane, PhysicsScene3D::plane2Sphere, PhysicsScene3D::plane2AABB,
	PhysicsScene3D::sphere2Plane, PhysicsScene3D::sphere2Sphere, PhysicsScene3D::sphere2AABB,
	PhysicsScene3D::AABB2Plane, PhysicsScene3D::AABB2Sphere, PhysicsScene3D::AABB2AABB,
};

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

bool PhysicsScene3D::plane2Plane(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	return false;
}

bool PhysicsScene3D::plane2Sphere(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	return sphere2Plane(obj2, obj1);
}

bool PhysicsScene3D::plane2AABB(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	return AABB2Plane(obj2, obj1);
}

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
			plane->resolveCollision(sphere);
			//sphere->setVelocity(glm::vec2(0, 0));
			return true;
		}
	}
	return false;
}

bool PhysicsScene3D::sphere2Sphere(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	// try to case objects to sphere and sphere
	Sphere3D *sphere1 = dynamic_cast<Sphere3D*>(obj1);
	Sphere3D *sphere2 = dynamic_cast<Sphere3D*>(obj2);
	// if we are successful then test for collision
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		glm::vec3 distance = sphere1->getPostition() - sphere2->getPostition();
		float radiusTotal = sphere1->getRadius() + sphere2->getRadius();

		if (glm::length(distance) <= radiusTotal)
		{
			sphere1->resolveCollision(sphere2);
			//sphere1->setVelocity(glm::vec2(0, 0));
			//sphere2->setVelocity(glm::vec2(0, 0));
			return true;
		}
	}
	return false;
}

bool PhysicsScene3D::sphere2AABB(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	Sphere3D *sphere1 = dynamic_cast<Sphere3D*>(obj1);
	Box3D *box1 = dynamic_cast<Box3D*>(obj2);

	if (box1 != nullptr && sphere1 != nullptr)
	{
		glm::vec3 A = glm::clamp(sphere1->getPostition(), box1->getMin(), box1->getMax());
		glm::vec3 V = A - sphere1->getPostition();

		if (glm::length(V) <= sphere1->getRadius())
		{
			sphere1->resolveCollision(box1);
		}
	}
	return false;
}

bool PhysicsScene3D::AABB2Plane(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	Box3D *box = dynamic_cast<Box3D*>(obj1);
	Plane3D *plane = dynamic_cast<Plane3D*>(obj2);

	if (box != nullptr && plane != nullptr)
	{
		glm::vec3 v = plane->getNormal();
		glm::vec3 bottomLeft = box->getMin();
		glm::vec3 bottomRight = box->getMin() + glm::vec3(box->getWidth(), 0, 0);
		glm::vec3 topLeft = box->getMin() + glm::vec3(0, box->getHight() , 0);
		glm::vec3 topRight = box->getMax() + glm::vec3(box->getWidth(), box->getHight(), box->getDepth());

		if (glm::dot(v, bottomLeft) - plane->getDistance() < 0 ||
			glm::dot(v, bottomRight) - plane->getDistance() < 0 ||
			glm::dot(v, topLeft) - plane->getDistance() < 0 ||
			glm::dot(v, topLeft) - plane->getDistance() < 0)
		{
			plane->resolveCollision(box);
			return true;
		}
	}

	return false;
}

bool PhysicsScene3D::AABB2Sphere(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	return sphere2AABB(obj2, obj1);
}

bool PhysicsScene3D::AABB2AABB(PhysicsObject3D* obj1, PhysicsObject3D* obj2)
{
	Box3D *box1 = dynamic_cast<Box3D*>(obj1);
	Box3D *box2 = dynamic_cast<Box3D*>(obj2);

	if (box1 != nullptr && box2 != nullptr)
	{
		glm::vec3 max1 = box1->getMax();
		glm::vec3 min1 = box1->getMin();
		glm::vec3 max2 = box2->getMax();
		glm::vec3 min2 = box2->getMin();

		if (min1.x <= max2.x &&
			min1.y <= max2.y &&
			max1.x >= min2.x &&
			max1.y >= min2.y)
		{
			box1->resolveCollision(box2);
			return true;
		}
	}
	return false;
}

void PhysicsScene3D::addActor(PhysicsObject3D * actor)
{
	m_actors.push_back(actor);
}
void PhysicsScene3D::removeActor(PhysicsObject3D* actor)
{
	std::remove(std::begin(m_actors), std::end(m_actors), actor);
}
void PhysicsScene3D::update(float dt)
{
	static std::list<PhysicsObject3D*> dirty;

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

	//check for collisions (ideally you'd want to ahve some sort of scenemanagment in place
	//for (auto pActor : m_actors) 
	//{
	//	for (auto pOther : m_actors) 
	//	{
	//		if (pActor == pOther)
	//			continue;
	//		if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() && std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
	//			continue;
	//		Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
	//		if (pRigid->CheckCollision(pOther) == true) 
	//		{
	//			pRigid->applyForceToActor(dynamic_cast<Rigidbody*>(pOther),
	//			pRigid->getVelocity() * pRigid->getMass());
	//
	//			dirty.push_back(pRigid);
	//			dirty.push_back(pOther);
	//		}
	//	}
	//	dirty.clear();
	//}
}
void PhysicsScene3D::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}
void PhysicsScene3D::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
		std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}
