#include "Renderer.h"


Renderer::Renderer(){
	this->windowWidth = 1068;
	this->windowHeight = 800;
	window = SDL_CreateWindow("Kyle Ahn - Particle Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	glContext = SDL_GL_CreateContext(window);
	this->numFrames = 0;
	this->lastTime = SDL_GetTicks();
	initiate();
}

Renderer::~Renderer(){
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
}

void Renderer::initiate(){
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.5, 0.5, 0.5, 1);
	setShaders();
}


void Renderer::setShaders(){
	GLuint program = glCreateProgram();

	string vertexString = loadShader("Imports/Shaders/vertexShader.glsl");
	string fragString = loadShader("Imports/Shaders/fragmentShader.glsl");

	const char *vertexChars = vertexString.c_str();
	const char *fragChars = fragString.c_str();

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexChars, NULL);
	glCompileShader(vertexShaderID);
	glAttachShader(program, vertexShaderID);

	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragChars, NULL);
	glCompileShader(fragmentShaderID);
	glAttachShader(program, fragmentShaderID);

	GLuint VERTEX_BUFFER = 0;
	GLuint COLOUR_BUFFER = 1;
	GLuint TEXTURE_BUFFER = 2;

	glBindAttribLocation(program, VERTEX_BUFFER, "position");
	glBindAttribLocation(program, COLOUR_BUFFER, "colour");
	glBindAttribLocation(program, TEXTURE_BUFFER, "texCoord");

	glLinkProgram(program);
	glUseProgram(program);

	this->colourVariation = glGetUniformLocation(program, "colourVar");
	this->pFixed = glGetUniformLocation(program, "pFixed");

	this->perspective = glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 5000.0f);
	ortho = glm::ortho(0.0f, (float)this->windowWidth, 0.0f, (float)this->windowHeight);
	glm::mat4 view = glm::mat4();
	glm::mat4 model = glm::mat4();

	shaderModelMat = glGetUniformLocation(program, "modelMatrix");
	glUniformMatrix4fv(shaderModelMat, 1, GL_FALSE, (float*)&model);
	shaderViewMat = glGetUniformLocation(program, "viewMatrix");
	glUniformMatrix4fv(shaderViewMat, 1, GL_FALSE, (float*)&view);
	shaderProjMat = glGetUniformLocation(program, "projMatrix");
	glUniformMatrix4fv(shaderProjMat, 1, GL_FALSE, (float*)&this->perspective);

	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_FALSE, (float*)&this->perspective);

	GLint sampler = glGetUniformLocation(program, "tex0");
	glUniform1i(sampler, 0);

}

void Renderer::update(){
	glClear(GL_COLOR_BUFFER_BIT);
	this->renderParticles();
	SDL_GL_SwapWindow(this->window);
	//get_fps();
}

void Renderer::renderParticles(){
	glUniform1f(this->pFixed, false);
	glBindVertexArray(this->particleSystem->particleVAO_ID);
	glBindTexture(GL_TEXTURE_2D, this->particleSystem->parseTexture);
	glUniformMatrix4fv(this->shaderProjMat, 1, GL_FALSE, (float*)&this->perspective);
	for (std::vector<Particle>::iterator i = this->particleSystem->particles.begin(); i != this->particleSystem->particles.end(); ++i){
		glUniformMatrix4fv(this->shaderModelMat, 1, GL_FALSE, (float*)&i->modelMatrix);
		glUniform1f(this->colourVariation, (float)i->lifeSpan / 3.6f);
		/*for (int j = 0; j < 60; j++) {
		if( j % 4 == 0)
		glDrawArrays(GL_TRIANGLE_STRIP, j, 4);
		}*/
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//glDrawArrays(GL_POINTS, 0, 3000);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}