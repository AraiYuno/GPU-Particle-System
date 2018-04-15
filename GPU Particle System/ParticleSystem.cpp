#include "ParticleSystem.h"
#include "Helper.h"
#include <SDL.h>
#include <algorithm>
#include <SOIL.h>

ParticleSystem::ParticleSystem(){
	this->isInitiated = true;
	this->setParticles();

	//
	this->gravity.x = 0, this->gravity.y = 8, this->gravity.z = 0;
	this->friction = 0.0f;

	int thisTime = SDL_GetTicks();
	deltaTime = (float)(thisTime - lastTime) / 1000;
	lastTime = thisTime;
}

void ParticleSystem::setParticles(){
	mapTexture(this->parseTexture, "Imports/Textures/fire.jpg");

	glm::vec2 texture[80][4];
	glm::vec3 position[80][4];
	glm::vec4 colour[80][4];
	float high = 2, low = -2;
	for (int i = 0; i < 80; i++) {
		float t1 = randomFloatBetween(0.f, 0.225f);
		float t2 = randomFloatBetween(0.f, 0.225f);
		float t3 = randomFloatBetween(0.f, 0.225f);
		texture[i][0] = glm::vec2(0.f, t1);
		texture[i][1] = glm::vec2(0.f, 0.f);
		texture[i][2] = glm::vec2(t2, t2);
		texture[i][3] = glm::vec2(t3, 0.f);
		for (int j = 0; j < 4; j++) {
			float r1 = randomFloatBetween(low, high);
			float r2 = randomFloatBetween(low, high);
			float r3 = randomFloatBetween(0, 1);
			position[i][j] = glm::vec3(r1, r2, -45.0f - r1);
			colour[i][j] = glm::vec4(1.0, 1.0, 0.0, r3);
		}
	}

	/*glm::vec2 texture[3000];
	glm::vec3 position[3000];
	glm::vec4 colour[3000];
	float high = 5, low = -5;
	for (int i = 0; i < 3000; i++) {
		float r1 = randomFloatBetween(-5, 5);
		float r2 = randomFloatBetween(-5, 5);;
		float r3 = randomFloatBetween(-5, 5);;
		position[i] = glm::vec3(r1, r2, -35.0f - r1);
		texture[i] = glm::vec2(r1, r3);
		if (r2 > 2.3f)
		colour[i] = glm::vec4(0.0, 0.0, 0.0, r1);
		else
		colour[i] = glm::vec4(1.0, 1.0, 0, r1);
	}*/

	GLuint posVBO;
	GLuint texVBO;
	GLuint colourVBO;

	glGenVertexArrays(1, &particleVAO_ID);
	glBindVertexArray(this->particleVAO_ID);

	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, /*3000*/ 4 * 80 * sizeof(glm::vec3), position, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &colourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferData(GL_ARRAY_BUFFER, /*3000*/ 4 * 80 * sizeof(glm::vec4), colour, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, /*3000*/ 4 * 80 * sizeof(glm::vec2), texture, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}


void ParticleSystem::update(){
	int thisTime = SDL_GetTicks();
	deltaTime = (float)(thisTime - lastTime) / 1000;
	lastTime = thisTime;


	for (std::vector<Particle>::iterator i = this->particles.begin(); i != this->particles.end();) {
		i->velocity = computeVelocity(i->velocity, i->acceleration + gravity, deltaTime);
		i->position = computeEuler(i->position, i->velocity, i->acceleration + gravity, deltaTime);
		i->lifeSpan -= deltaTime;
		if (i->lifeSpan <= 0.0f)
			i = this->particles.erase(i);
		else ++i;
	}

	for (std::vector<Particle>::iterator i = particles.begin(); i != particles.end(); ++i)
		i->update();

	for (int i = 0; i < deltaTime * 3000; ++i) this->particles.push_back(Particle());
	std::sort(this->particles.begin(), this->particles.end(), Particle::sortParticles);
}