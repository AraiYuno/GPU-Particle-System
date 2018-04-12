#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <gl\glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include <string>
#include <sstream>
#include "ParticleSystem.h"
#include "Helper.h"

using namespace std;

class Renderer
{
public:
	SDL_Window * window;
	int  windowWidth;
	int  windowHeight;

	ParticleSystem *particleSystem;
	SDL_GLContext glContext;
	GLint shaderModelMat;
	GLint shaderViewMat;
	GLint shaderProjMat;
	GLint shaderOrthoMat;
	GLint colourVariation;
	GLint pFixed;
	glm::mat4 perspective;
	glm::mat4 ortho;
	int numFrames;
	int lastTime;

	Renderer();
	~Renderer();
	void initiate();
	void setShaders();
	void renderParticles();
	void update();
};

#endif