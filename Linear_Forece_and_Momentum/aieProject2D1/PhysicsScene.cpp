#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Rigidbody.h"
#include <iostream>
#include <algorithm>
#include <list>


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
