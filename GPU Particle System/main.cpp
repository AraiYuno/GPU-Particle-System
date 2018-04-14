#include "Renderer.h"

int main(int argc, char* args[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	Renderer renderer;
	ParticleSystem *particleSystem = new ParticleSystem;
	renderer.particleSystem = particleSystem;

	while (true) 
		renderer.update();

	delete particleSystem;
	SDL_Quit();
	return 0;
}