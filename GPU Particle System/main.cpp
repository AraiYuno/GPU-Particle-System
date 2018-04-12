#include "Renderer.h"
#include "Physics.h"

int main(int argc, char* args[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	Renderer renderer;
	Physics physics;
	ParticleSystem *particleSystem = new ParticleSystem;
	renderer.particleSystem = particleSystem;
	physics.particleSystem = particleSystem;
	while (particleSystem->isInitiated) {
		renderer.update();
		physics.update();
	}
	delete particleSystem;
	SDL_Quit();
	return 0;
}