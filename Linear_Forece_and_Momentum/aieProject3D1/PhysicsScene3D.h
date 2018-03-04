#pragma once
#include <glm/ext.hpp>
#include <algorithm>
#include <vector>

class PhysicsObject3D;

class PhysicsScene3D
{
public:
	//----------------------------------------------------------------------------------------------
	//default constructer
	//----------------------------------------------------------------------------------------------
	PhysicsScene3D();
	//----------------------------------------------------------------------------------------------
	// defualt destructor
	//----------------------------------------------------------------------------------------------
	~PhysicsScene3D();
	//----------------------------------------------------------------------------------------------
	// Adds an actor from the actor array in the physicsScene
	//
	// Param:
	//		actor: A physicsObject pointer which gets added to the actor array
	//----------------------------------------------------------------------------------------------
	void addActor(PhysicsObject3D* actor);
	//----------------------------------------------------------------------------------------------
	// Removes an actor from the actor array in the physicsScene
	//
	// Param:
	//		actor: A physicsObject pointer which gets remove from the scene
	//----------------------------------------------------------------------------------------------
	void removeActor(PhysicsObject3D* actor);
	//----------------------------------------------------------------------------------------------
	// Updates actors and checks for collision
	//
	// Param:
	//		dt: A float which represents deltatime which increases over time
	//----------------------------------------------------------------------------------------------
	void update(float dt);
	//----------------------------------------------------------------------------------------------
	// Updates each actors gizmos every frame
	//----------------------------------------------------------------------------------------------
	void updateGizmos();
	//----------------------------------------------------------------------------------------------
	// Used only for debug purpose
	//----------------------------------------------------------------------------------------------
	void debugScene();
	//----------------------------------------------------------------------------------------------
	// sets physicsScene gravity
	//
	// Param:
	//		gravity: A vec3 which sets physicsScene m_gravity
	//----------------------------------------------------------------------------------------------
	void setGravity(const glm::vec3 gravity) { m_gravity = gravity; }
	//----------------------------------------------------------------------------------------------
	// Gets physicsScene m_gravity
	//
	// Return:
	//		Returns a vec3 m_gravity
	//----------------------------------------------------------------------------------------------
	glm::vec3 getGravity() const { return m_gravity; }
	//----------------------------------------------------------------------------------------------
	// sets physicsScene timeStep
	//
	// Param:
	//		timeStep: A float which sets physicsScene m_timeStep
	//----------------------------------------------------------------------------------------------
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	//----------------------------------------------------------------------------------------------
	// Gets physicsScene timeStep
	//
	// Return:
	//		Returns a float m_timeStep
	//----------------------------------------------------------------------------------------------
	float getTimeStep() const { return m_timeStep; }
	//----------------------------------------------------------------------------------------------
	// Checks for collision iterats through shapes calls a funtionptr which calls one of the many 
	// collision functions based on the shapes
	//----------------------------------------------------------------------------------------------
	void checkForCollision();
	//----------------------------------------------------------------------------------------------
	// Checks for collision between two planes
	//
	// Param:
	//		obj1: A physicsObject pointer used to help resolve the collision
	//		obj2: Another physicsObject pointer used to help resolve the collision
	// Return:
	//		Returns false because we will not need to check is two planes collide
	//----------------------------------------------------------------------------------------------
	static bool plane2Plane(PhysicsObject3D*, PhysicsObject3D*);
	//----------------------------------------------------------------------------------------------
	// Checks for collision between plane2Sphere
	//
	// Param:
	//		obj1: A physicsObject pointer used to help resolve the collision
	//		obj2: Another physicsObject pointer used to help resolve the collision
	// Return:
	//		Returns sphere2Plane which resolves the collision if there is any
	//----------------------------------------------------------------------------------------------
	static bool plane2Sphere(PhysicsObject3D*, PhysicsObject3D*);
	//----------------------------------------------------------------------------------------------
	// Checks for collision between plane2Box
	//
	// Param:
	//		obj1: A physicsObject pointer used to help resolve the collision
	//		obj2: Another physicsObject pointer used to help resolve the collision
	// Return:
	//		Returns box2Plane which resolves the collision if there is any
	//----------------------------------------------------------------------------------------------
	static bool plane2Box(PhysicsObject3D*, PhysicsObject3D*);
	//static bool plane2AABB(PhysicsObject3D*, PhysicsObject3D*);
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
	static bool sphere2Plane(PhysicsObject3D*, PhysicsObject3D*);
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
	static bool sphere2Sphere(PhysicsObject3D*, PhysicsObject3D*);
	//----------------------------------------------------------------------------------------------
	// Checks for collision between sphere2Box
	//
	// Param:
	//		obj1: A physicsObject pointer used to help resolve the collision
	//		obj2: Another physicsObject pointer used to help resolve the collision
	// Return:
	//		Returns box2Sphere which resolves the collision if there is any
	//----------------------------------------------------------------------------------------------
	static bool sphere2Box(PhysicsObject3D*, PhysicsObject3D*);
	/*static bool sphere2AABB(PhysicsObject3D*, PhysicsObject3D*);
	static bool AABB2Plane(PhysicsObject3D*, PhysicsObject3D*);
	static bool AABB2Sphere(PhysicsObject3D*, PhysicsObject3D*);
	static bool AABB2AABB(PhysicsObject3D*, PhysicsObject3D*);*/
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
	static bool Box2Box(PhysicsObject3D*, PhysicsObject3D*);
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
	static bool Box2Sphere(PhysicsObject3D*, PhysicsObject3D*);
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
	static bool Box2Plane(PhysicsObject3D*, PhysicsObject3D*);

protected:
	glm::vec3 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject3D*> m_actors;
};

