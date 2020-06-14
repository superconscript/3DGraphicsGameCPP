#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include "Shader.h"
#include "gameEngine.h"

class OpenGLManager {
public:
	OpenGLManager(SDL_Window* glWindow, gameEngine* gEngine);
	~OpenGLManager();

	void glewInitialize() { glewInit(); }

	//void initShaders();

	void update();

	void render();

	void setIsGLRunning(bool isRunning) { isGLRunning = isRunning; }

	bool getIsGLRunning() { return isGLRunning; }

	void initShaders();

//	bool RenderSomething(GLuint gProgramID); // bool is whether is was successful
	bool RenderSomething(SDL_Window* glWindow); // bool is whether is was successful
	// Need to create draw functinos
	void renderTriangle(GLuint VAO, GLuint VBO, GLuint gProgramID);
	//bool createGLWindow(int width, int height, int flags);
	
private:
	float timeValue = 0;
	//float timeDiff = 0;
	GLuint gProgramID;
	SDL_Window* glWindow;
	SDL_GLContext glContext;
	gameEngine* gEngine; // the game engine
	bool isGLRunning = false;
	//GLint gVertextPos2dLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;
	GLuint VAO;
	bool success;
	char infoLog[512];
	//SDL_Window* glWindow;
};