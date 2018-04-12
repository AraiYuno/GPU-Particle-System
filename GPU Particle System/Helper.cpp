#include "Helper.h"


//===========================================================================
// mapTexture
//   a function to load and map an image as a texture. 
//
//   Source: https://open.gl/textures
//===========================================================================
void mapTexture(GLuint &tex, const char *name){
	int width, height, channels;
	unsigned char *texData = SOIL_load_image(name, &width, &height, &channels, 0);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
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



glm::vec3 computeVelocity(glm::vec3 u, glm::vec3 a, float t){
	return (u + a * t);
}

//===========================================================================
// computeEuler
//   computes euler simply
//===========================================================================
glm::vec3 computeEuler(glm::vec3 s, glm::vec3 u, glm::vec3 a, float t){
	return computeVelocity(s, computeVelocity(u, a, t), t);
}