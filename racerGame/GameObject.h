#pragma once
#include"math.h"
#include "gameEngine.h"
//Paddle Settings
//int paddleHeight1 = 100;
//int paddleWidth1 = 40;

class gameObject {
public:
	gameObject(char* texture1, vector2d size, vector2d position, SDL_Renderer* renderer);
	~gameObject();
	void Render();







protected:
	SDL_Rect* r;
	const char* texture;
	vector2d position;
	vector2d size;
	SDL_Renderer* renderer;
};

class Racer : protected gameObject{
public:
	Racer(char* texture, vector2d size, vector2d position, SDL_Renderer* renderer);
	~Racer();

	void Move();
protected:

};

class aiRacer : protected Racer {
public:
	aiRacer(char* texture, vector2d size, vector2d position, SDL_Renderer* renderer, int aiType);
	~aiRacer();
private:
	int Type;


};
// Player needs to be able to control their position
class playerRacer : protected Racer {
public:
	playerRacer(char* texture, vector2d size, vector2d position, SDL_Renderer* renderer) : Racer(texture, size, position, renderer) {};
	~playerRacer();
private:


};