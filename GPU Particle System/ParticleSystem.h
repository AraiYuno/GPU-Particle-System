#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "GL\glew.h"
#include "Particle.h"
#include <vector>

class ParticleSystem
{
public:
	GLuint particleVAO_ID;
	GLuint parseTexture;
	GLuint playerTex;
	GLuint poinTex;

	// Particle System properties
	glm::vec3 gravity;
	int lastTime;
	float deltaTime;
	float friction;
	float invCount;

	std::vector<Particle> particles;
	bool isInitiated;

	ParticleSystem();
	void setParticles();
	void update();


};

#endif