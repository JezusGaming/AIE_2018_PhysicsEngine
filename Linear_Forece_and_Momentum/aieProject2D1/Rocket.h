#pragma once
#include "Sphere.h"
class Rocket : public Sphere
{
public:
	Rocket(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
	~Rocket();

	bool checkRocket(float dt);

	float m_fFuelConsumption = 1.0f;

protected:
	float m_fFuel = 0.0f;
	float m_fTimer = 0.0f;
	float m_fFuelSpeed = 0.001;
};

