#include "aieProject2D1App.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <glm\ext.hpp>
#include <Gizmos.h>

aieProject2D1App::aieProject2D1App() {

}

aieProject2D1App::~aieProject2D1App() {

}

bool aieProject2D1App::startup() {
	
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimeStep(0.01f);

	float radius = 1.0f;
	float speed = 30;
	glm::vec2 startPos(-40, 0);
	float inclination = (float)3.14f / 3.5f;

	m_physicsScene->addActor(new Sphere(startPos, inclination, speed, 1, radius, glm::vec4(1, 0, 0, 1)));

	setupConinuousDemo(startPos, inclination, speed, -10);

	//Sphere* ball;
	//Sphere* ball1;
	//ball = new Sphere(glm::vec2(-20, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 0, 1));
	//ball1 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1));
	//m_physicsScene->addActor(ball);
	//m_physicsScene->addActor(ball1);
	//
	//ball->applyForce(glm::vec2(15, 0));
	//ball1->applyForce(glm::vec2(-30, 0));
	//ball->applyForceToActor(ball1, glm::vec2(2,0));

	rocket = new Rocket(glm::vec2(0,0), glm::vec2(0,0), 4000.0f, 10, glm::vec4(1, 0, 0, 1));
	m_physicsScene->addActor(rocket);

	return true;
}

void aieProject2D1App::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void aieProject2D1App::setupConinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
{
	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);

	while (t <= 5)
	{
		glm::vec2 incl = glm::vec2(sin(inclination), cos(inclination));

		float x = startPos.x + (incl.x * speed * t);
		float y = startPos.y + (incl.y * speed * t) + ((gravity * t*t) /2.0f);

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
		t += tStep;
	}
}

void aieProject2D1App::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exhaust for rocket
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		if (rocket->checkRocket(deltaTime))
		{
			Sphere* exhaust;

			exhaust = new Sphere(rocket->getPostition(), rocket->getVelocity(), rocket->m_fFuelConsumption, 1, glm::vec4(1, 1, 0, 1));
			m_physicsScene->addActor(exhaust);

			rocket->applyForceToActor(exhaust, glm::vec2(0, -1000));
		}

	}
	
	//static const glm::vec4 colours[] = {
	//	glm::vec4(1,0,0,1), glm::vec4(0,1,0,1),
	//	glm::vec4(0,0,1,1), glm::vec4(0.8f,0,0.5f,1),
	//	glm::vec4(0,1,1,1)
	//};
	//
	//static const int rows = 5;
	//static const int columns = 10;
	//static const int hSpace = 1;
	//static const int vSpace = 1;
	//
	//static const glm::vec2 scrExtents(100, 50);
	//static const glm::vec2 boxExtents(7, 3);
	//static const glm::vec2 startPos(
	//	-(columns >> 1)*((boxExtents.x * 2) + vSpace) + boxExtents.x + (vSpace / 2.0f),
	//	scrExtents.y - ((boxExtents.y * 2) + hSpace));

	// draw the grid blocks
	//glm::vec2 pos;
	//for (int y = 0; y < rows; y++) {
	//	pos = glm::vec2(startPos.x, startPos.y - (y* ((boxExtents.y * 2) + hSpace)));
	//	for (int x = 0; x < columns; x++) {
	//		aie::Gizmos::add2DAABBFilled(pos, boxExtents, colours[y]);
	//		pos.x += (boxExtents.x * 2) + vSpace;
	//	}
	//}

	// draw ball
	//aie::Gizmos::add2DCircle(glm::vec2(0, -35), 3, 12, glm::vec4(1, 1, 0, 1));
	//aie::Gizmos::add2DCircle(glm::vec2(0, 0), 30, 30, glm::vec4(1, 1, 0, 1));
	//aie::Gizmos::add2DCircle(glm::vec2(-15, 10), 3, 12, glm::vec4(0, 0, 0, 1));
	//aie::Gizmos::add2DCircle(glm::vec2(15, 10), 3, 12, glm::vec4(0, 0, 0, 1));
	//aie::Gizmos::add2DCircle(glm::vec2(-15, 10), 1, 12, glm::vec4(1, 0, 0, 1));
	//aie::Gizmos::add2DCircle(glm::vec2(15, 10), 1, 12, glm::vec4(1, 0, 0, 1));
	//aie::Gizmos::add2DAABBFilled(glm::vec2(0, -20), glm::vec2(8, 2), glm::vec4(0, 0, 0, 1));
	//aie::Gizmos::add2DTri(glm::vec2(10, 0), glm::vec2(12,12), glm::vec2(6, 6), glm::vec4(1,1,1,1));
	//aie::Gizmos::add2DAABBFilled(glm::vec2(-10, -18), glm::vec2(2, 4), glm::vec4(0, 0, 0, 1));
	//aie::Gizmos::add2DAABBFilled(glm::vec2(10, -18), glm::vec2(2, 4), glm::vec4(0, 0, 0, 1));
	// draw the player's paddle
	//aie::Gizmos::add2DAABBFilled(glm::vec2(0, -40), glm::vec2(12, 2),
								 //glm::vec4(1, 0, 1, 1));

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void aieProject2D1App::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	//aie::Gizmos::draw2D(glm::ortho<float>(-640, 640, -640 / aspectRatio, 640 / aspectRatio, -1.0f, 1.0f)); // pixel perfect for 1280 /720
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}