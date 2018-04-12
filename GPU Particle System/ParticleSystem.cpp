#include "ParticleSystem.h"
#include <SOIL.h>

ParticleSystem::ParticleSystem(){
	this->isInitiated = true;
	this->setParticles();
}

void ParticleSystem::setParticles(){
	mapTexture(this->parseTexture, "Imports/Textures/fire.jpg");

	glm::vec2 tex[80][4];
	glm::vec3 pos[80][4];
	glm::vec4 colour[80][4];
	float high = 5, low = -5;
	for (int i = 0; i < 80; i++) {
		tex[i][0] = glm::vec2(0, 0);
		tex[i][1] = glm::vec2(0.2, 0);
		tex[i][2] = glm::vec2(0.2, 0.2);
		tex[i][3] = glm::vec2(0.0, 0.2);
		for (int j = 0; j < 4; j++) {
			float r1 = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - (low))));
			float r2 = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - (low))));
			float r3 = -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-1))));
			pos[i][j] = glm::vec3(r1, r2, -45.0f - r1);
			//tex[i] = glm::vec2(r1, r2);
			if (r2 > 2.5f)
				colour[i][j] = glm::vec4(0.0, 0.0, 0.0, r3);
			else
				colour[i][j] = glm::vec4(1.0, 1.0, 0, r3);
		}
	}

	//glm::vec2 tex[3000];
	//glm::vec3 pos[3000];
	//glm::vec4 colour[3000];
	//float high = 5, low = -5;
	//for (int i = 0; i < 3000; i++) {
	//	float r1 = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - (low))));
	//	float r2 = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - (low))));
	//	float r3 = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - (low))));
	//	pos[i] = glm::vec3(r1, r2, -35.0f - r1);
	//	tex[i] = glm::vec2(r1, r3);
	//	if (r2 > 2.5f)
	//	colour[i] = glm::vec4(0.0, 0.0, 0.0, r1);
	//	else
	//	colour[i] = glm::vec4(1.0, 1.0, 0, r1);
	//}

	GLuint posVBO;
	GLuint texVBO;
	GLuint colourVBO;

	glGenVertexArrays(1, &particleVAO_ID);
	glBindVertexArray(this->particleVAO_ID);

	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, /*3000*/ 4 * 80 * sizeof(glm::vec3), pos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &colourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferData(GL_ARRAY_BUFFER, /*3000*/ 4 * 80 * sizeof(glm::vec4), colour, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, /*3000*/ 4 * 80 * sizeof(glm::vec2), tex, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}


void ParticleSystem::update(){
	for (std::vector<Particle>::iterator i = particles.begin(); i != particles.end(); ++i) 
		i->update();
}