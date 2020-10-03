#pragma once
#include"math.h"
#include "gameEngine.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
//Paddle Settings
//int paddleHeight1 = 100;
//int paddleWidth1 = 40;
struct BoundingBox {
	BoundingBox();
	~BoundingBox();
	//4 vec3's for each vertice of box
	glm::vec3 verticeTable[4];
//	glm::vec3 vertice1;
	//glm::vec3 vertice2;
	//glm::vec3 vertice3;
//	glm::vec4 vertice4;
};



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
