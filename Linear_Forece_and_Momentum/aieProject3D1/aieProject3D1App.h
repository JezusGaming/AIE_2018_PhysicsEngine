#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "PhysicsScene3D.h"
#include "Sphere3D.h"
#include "Plane3D.h"
#include "Box3D.h"
#include "BoxOOB.h"
#include <vector>

class aieProject3D1App : public aie::Application {
public:

	aieProject3D1App();
	virtual ~aieProject3D1App();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	PhysicsScene3D* m_physicsScene;

	Sphere3D* sphere;
	Sphere3D* sphere1;
	int circleCounter;
	Sphere3D* sphereList[5];
};