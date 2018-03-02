#include "aieProject3D1App.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <imgui.h>
#include <vector>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

aieProject3D1App::aieProject3D1App() {

}

aieProject3D1App::~aieProject3D1App() {

}

bool aieProject3D1App::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(30), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	m_physicsScene = new PhysicsScene3D();
	m_physicsScene->setGravity(glm::vec3(0, -9.8f, 0));
	m_physicsScene->setTimeStep(0.01f);

	Sphere3D* sphere;
	Sphere3D* sphere1;
	sphere = new Sphere3D(glm::vec3(5, 5, 0), glm::vec3(-10, 0, 0), 3.0f, 2, glm::vec4(1, 0, 0, 1));
	sphere1 = new Sphere3D(glm::vec3(-5, 5, 1), glm::vec3(10, 0, 0), 3.0f, 2, glm::vec4(0, 1, 0, 1));
	//sphere->applyForce(glm::vec3(-10, 0, 0));
	//sphere1->applyForce(glm::vec3(10, 0, 0));
	m_physicsScene->addActor(sphere);
	m_physicsScene->addActor(sphere1);

	BoxOOB* box;
	BoxOOB* box1;
	box = new BoxOOB(glm::vec3(-5, 10, 5), glm::vec3(10, 0, 0), 4.0f, 2, 2, 2, glm::vec4(1, 0, 0, 1));
	box1 = new BoxOOB(glm::vec3(5, 10, 5), glm::vec3(-10, 0, 0), 4.0f, 2, 2, 2, glm::vec4(0, 1, 0, 1));
	//box->applyForce(glm::vec3(10, 0, 0));
	//box1->applyForce(glm::vec3(-10, 0, 0));
	m_physicsScene->addActor(box);
	m_physicsScene->addActor(box1);
	
	Plane3D* plane;
	plane = new Plane3D(glm::normalize(glm::vec3(0, 1, 0)), 0);
	m_physicsScene->addActor(plane);

	m_clearColour = glm::vec4(1, 1, 1, 1);

	return true;
}

void aieProject3D1App::shutdown() {

	Gizmos::destroy();
}

void aieProject3D1App::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();
	Sphere3D* sphere;
	std::vector<Sphere3D*> m_spheres;
	ImGui::Begin("My Options");
		ImGui::ColorEdit3("clear colour", glm::value_ptr(m_clearColour));
		if (ImGui::Button("Spawn shape", ImVec2(50, 50)))
		{
			
			sphere = new Sphere3D(glm::vec3(0, 15, 0), glm::vec3(0, 0, 0), 3.0f, 2, glm::vec4(0, 0, 1, 1));
			m_physicsScene->addActor(sphere);
			m_spheres.push_back(sphere);
		}
		if (ImGui::Button("Remove shape", ImVec2(50, 50)))
		{
			m_physicsScene->removeActor(m_spheres[0]);
			m_spheres.pop_back();
		}
	ImGui::End();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void aieProject3D1App::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}