#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "GL\glew.h"
#include "Particle.h"
#include "Helper.h"
#include <vector>

class ParticleSystem
{
public:
	GLuint particleVAO_ID;
	GLuint parseTexture;
	GLuint playerTex;
	GLuint poinTex;

	std::vector<Particle> particles;
	bool isInitiated;

	ParticleSystem();
	void setParticles();
	void update();
};

#endif