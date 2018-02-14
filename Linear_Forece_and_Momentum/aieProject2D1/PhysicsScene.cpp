#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Rigidbody.h"
#include <iostream>
#include <algorithm>
#include <list>
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0,0))
{

}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		pActor;
	}
}

static fn collisionFunctionArray[] =
{
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2AABB, 
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2AABB, 
	PhysicsScene::AABB2Plane, PhysicsScene::AABB2Sphere, PhysicsScene::AABB2AABB,
};

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	// need to check for collisions against all objects except this one.
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
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

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return sphere2Plane(obj2, obj1);
}

bool PhysicsScene::plane2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return AABB2Plane(obj2, obj1);
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere *sphere = dynamic_cast<Sphere*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);

	// if we are successful then test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();
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

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// try to case objects to sphere and sphere
	Sphere *sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere *sphere2 = dynamic_cast<Sphere*>(obj2);
	// if we are successful then test for collision
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		glm::vec2 distance = sphere1->getPostition() - sphere2->getPostition();
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

bool PhysicsScene::sphere2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere *sphere1 = dynamic_cast<Sphere*>(obj1);
	Box *box1 = dynamic_cast<Box*>(obj2);

	if (box1 != nullptr && sphere1 != nullptr)
	{
		glm::vec2 A = glm::clamp(sphere1->getPostition(), box1->getMin(), box1->getMax());
		glm::vec2 V = A - sphere1->getPostition();
		
		if (glm::length(V) <= sphere1->getRadius())
		{
			sphere1->resolveCollision(box1);
		}
	}
	return false;
}

bool PhysicsScene::AABB2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box *box = dynamic_cast<Box*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);

	if (box != nullptr && plane != nullptr)
	{
		glm::vec2 v = plane->getNormal();
		glm::vec2 bottomLeft = box->getMin();
		glm::vec2 bottomRight = box->getMin() + glm::vec2(box->getWidth(), 0);
		glm::vec2 topLeft = box->getMin() + glm::vec2(0, box->getHight());
		glm::vec2 topRight = box->getMax() + glm::vec2(box->getWidth(), box->getHight());

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

bool PhysicsScene::AABB2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return sphere2AABB(obj2, obj1);
}

bool PhysicsScene::AABB2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box *box1 = dynamic_cast<Box*>(obj1);
	Box *box2 = dynamic_cast<Box*>(obj2);

	if (box1 != nullptr && box2 != nullptr)
	{
		glm::vec2 max1 = box1->getMax();
		glm::vec2 min1 = box1->getMin();
		glm::vec2 max2 = box2->getMax();
		glm::vec2 min2 = box2->getMin();

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

void PhysicsScene::addActor(PhysicsObject * actor)
{
	m_actors.push_back(actor);
}
void PhysicsScene::removeActor(PhysicsObject* actor)
{
	std::remove(std::begin(m_actors), std::end(m_actors), actor);
}
void PhysicsScene::update(float dt)
{
	static std::list<PhysicsObject*> dirty;

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
void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}
void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
		std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}
