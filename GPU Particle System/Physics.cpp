#include "Physics.h"
#include "Helper.h"
#include <SDL.h>
#include <algorithm>

Physics::Physics(){
	this->gravity.x = 0, this->gravity.y = 8, this->gravity.z = 0;
	this->friction = 0.9f;
}

void Physics::initiate(){
	int thisTime = SDL_GetTicks();
	deltaTime = (float)(thisTime - lastTime) / 1200;
	lastTime = thisTime;
}

void Physics::update(){
	int thisTime = SDL_GetTicks();
	deltaTime = (float)(thisTime - lastTime) / 1200;
	lastTime = thisTime;

	this->particleSystem->update();

	for (std::vector<Particle>::iterator i = this->particleSystem->particles.begin(); i != this->particleSystem->particles.end();){
		i->position = computeEuler(i->position, i->velocity, i->acceleration + gravity, deltaTime);
		i->velocity = computeVelocity(i->velocity, i->acceleration + gravity, deltaTime);
		i->lifeSpan += deltaTime;
		if (i->lifeSpan >= 1.7f) 
			i = this->particleSystem->particles.erase(i);
		else ++i;
	}

	for (int i = 0; i < deltaTime * 3000; ++i) this->particleSystem->particles.push_back(Particle());
	std::sort(this->particleSystem->particles.begin(), this->particleSystem->particles.end(), Particle::sortParticles);
}