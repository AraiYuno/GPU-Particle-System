#include "Helper.h"


//===========================================================================
// mapTexture
//   a function to load and map an image as a texture. 
//
//   Source: https://open.gl/textures
//===========================================================================
void mapTexture(GLuint &texture, const char *name){
	int width, height, channels;
	unsigned char *texData = SOIL_load_image(name, &width, &height, &channels, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA8 : GL_RGB8, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}


string loadShader(const string &file_name){
	string line, r_string;
	ifstream file(file_name);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			r_string.append(line);
			r_string.append("\n");
		}
		file.close();
	}
	return r_string;
}


float randomFloatBetween(float low, float high) {
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - (low))));
}

float isInBetween(float _number) {
	float toReturn = 1.f;
	if (_number <= -40.f && _number > -41.f)
			toReturn = 0.9f;
	else if (_number <= -41.f && _number > -42.f)
		toReturn = 0.8f;
	else if (_number <= -42.f && _number > -43.f)
		toReturn = 0.7f;
	else if (_number <= -43.f && _number > -44.f)
		toReturn = 0.6f;
	else if (_number <= -44.f && _number > -45.f)
		toReturn = 0.5f;
	else if (_number <= -45.f && _number > -46.f)
		toReturn = 0.4f;
	else if (_number <= -46.f && _number > -47.f)
		toReturn = 0.3f;
	else if (_number <= -47.f && _number > -48.f)
		toReturn = 0.2f;
	else if (_number <= -48.f && _number > -49.f)
		toReturn = 0.1f;
	else if (_number <= -49.f && _number >= -50.f)
		toReturn = 0.05f;
	return toReturn;
}

//===========================================================================
// computeVelocity
//   newV = v + a * t. to calcualte the new velocity after deltatime.
//===========================================================================
glm::vec3 computeVelocity(glm::vec3 _velocity, glm::vec3 _acceleration, float _deltaTime){
	return (_velocity + _acceleration * _deltaTime);
}

//===========================================================================
// computeEuler
//   computes euler simply to return the new position of a particle.
//===========================================================================
glm::vec3 computeEuler(glm::vec3 _position, glm::vec3 _velocity, glm::vec3 _acceleration, float _deltaTime){
	return computeVelocity(_position, computeVelocity(_velocity, _acceleration, _deltaTime), _deltaTime);
}