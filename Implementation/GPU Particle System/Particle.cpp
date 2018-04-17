#include "Particle.h"
#include "Helper.h"
#include <iostream>

using namespace std;

Particle::Particle(){
	this->position = glm::vec3(0.f, -10.f, 0.f);
	this->lifeSpan = randomFloatBetween(1.4f, 1.9f);
	glm::vec3 newVelocity = glm::vec3(generateRandomFloat(), generateRandomFloat(), generateRandomFloat());
	while (glm::length(newVelocity) > 10)
		newVelocity = glm::vec3(generateRandomFloat(), generateRandomFloat(), generateRandomFloat());
	this->velocity = newVelocity;
	acceleration = glm::vec3(-0.8 * newVelocity.x, 0, -0.8 * newVelocity.z);
	modelMatrix = glm::translate(glm::mat4(), glm::vec3(this->position.x, this->position.y, this->position.z));
}

Particle::Particle(float _x, float _y, float _z){
	this->position = glm::vec3(_x, _y, _z);
	this->velocity = glm::vec3(-25, 25, 25);
	this->acceleration = glm::vec3(0, 0, 0);
	this->lifeSpan = randomFloatBetween(1.4f, 1.9f);
	modelMatrix = glm::translate(glm::mat4(), glm::vec3(this->position.x, this->position.y, this->position.z));
}

void Particle::update(){
	modelMatrix = glm::translate(glm::mat4(), glm::vec3(this->position.x, this->position.y, this->position.z));
}

bool Particle::sortParticles(Particle _particleA, Particle _particleB){
	return _particleB.position.z > _particleA.position.z;
}


float Particle::generateRandomFloat() {
	return (rand() % 2000 - 1000) / 100.0f;
}