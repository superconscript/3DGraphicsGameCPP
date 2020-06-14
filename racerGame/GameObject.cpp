#include "GameObject.h"
#include "TextureManager.h"

//Paddle Sizing Settings

// We need a racer class.

//GameObject BaseClass

gameObject::gameObject(char* texture1, vector2d size, vector2d position, SDL_Renderer* renderer)
	: texture(texture1) {

	this->size = size;
	this->position = position;
	this->renderer = renderer;
	this->r->h = size.y;
	this->r->w = size.x;

};
	// Load Image of Game Object
void gameObject::Render() {
	TextureManager::LoadTexture(this->texture, this->renderer);
};

// Racer BaseClass (inherits gameObject)
Racer::Racer(char* texture1, vector2d size, vector2d position, SDL_Renderer* renderer)
	: gameObject(texture1, size, position, renderer) {

};

// AI Racer inherits Racer
aiRacer::aiRacer(char* texture1, vector2d size, vector2d position, SDL_Renderer* renderer, int aiType)
	: Racer(texture1, size, position, renderer) {

};
// Player Racer inherits Racer;
