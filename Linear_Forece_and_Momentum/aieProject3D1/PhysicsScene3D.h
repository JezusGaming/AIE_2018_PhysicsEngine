#pragma once
#include <glm/ext.hpp>
#include <algorithm>
#include <vector>

class PhysicsObject3D;

class PhysicsScene3D
{
public:
	PhysicsScene3D();
	~PhysicsScene3D();

	void addActor(PhysicsObject3D* actor);
	void removeActor(PhysicsObject3D* actor);
	void update(float dt);
	void updateGizmos();
	void debugScene();

	void setGravity(const glm::vec3 gravity) { m_gravity = gravity; }
	glm::vec3 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void checkForCollision();

	static bool plane2Plane(PhysicsObject3D*, PhysicsObject3D*);
	static bool plane2Sphere(PhysicsObject3D*, PhysicsObject3D*);
	static bool plane2Box(PhysicsObject3D*, PhysicsObject3D*);
	//static bool plane2AABB(PhysicsObject3D*, PhysicsObject3D*);
	static bool sphere2Plane(PhysicsObject3D*, PhysicsObject3D*);
	static bool sphere2Sphere(PhysicsObject3D*, PhysicsObject3D*);
	static bool sphere2Box(PhysicsObject3D*, PhysicsObject3D*);
	/*static bool sphere2AABB(PhysicsObject3D*, PhysicsObject3D*);*/
	/*static bool AABB2Plane(PhysicsObject3D*, PhysicsObject3D*);
	static bool AABB2Sphere(PhysicsObject3D*, PhysicsObject3D*);
	static bool AABB2AABB(PhysicsObject3D*, PhysicsObject3D*);*/
	static bool Box2Box(PhysicsObject3D*, PhysicsObject3D*);
	static bool Box2Sphere(PhysicsObject3D*, PhysicsObject3D*);
	static bool Box2Plane(PhysicsObject3D*, PhysicsObject3D*);

protected:
	glm::vec3 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject3D*> m_actors;
};

