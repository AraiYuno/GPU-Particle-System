#ifndef PHYSICS_H
#define PHYSICS_H

#include "ParticleSystem.h"

class Physics
{
public:
	ParticleSystem * particleSystem;
	glm::vec3 gravity;
	int lastTime;
	float deltaTime;
	float friction;
	float invCount;

	Physics();
	void update();
	void initiate();
};

#endif