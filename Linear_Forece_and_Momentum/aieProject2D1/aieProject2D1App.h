#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"
#include "Rocket.h"


class aieProject2D1App : public aie::Application {
public:

	aieProject2D1App();
	virtual ~aieProject2D1App();

	virtual bool startup();
	virtual void shutdown();

	void setupConinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity);

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	PhysicsScene* m_physicsScene;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Rocket* rocket;
};