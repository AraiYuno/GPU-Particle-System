#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <fstream>
#include "GL\glew.h"
#include "SOIL.h"
#include "glm\glm.hpp"

using namespace std;

void mapTexture(GLuint &tex, const char *name);
string loadShader(const string &file_name);
glm::vec3 computeVelocity(glm::vec3 u, glm::vec3 a, float t);
glm::vec3 computeEuler(glm::vec3 s, glm::vec3 u, glm::vec3 a, float t);

#endif