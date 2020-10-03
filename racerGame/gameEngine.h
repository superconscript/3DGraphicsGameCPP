#pragma once

//#ifdef gameEngine.h
//#define gameEngine.h

#include <SDL.h>
#include <stdio.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
//#include<string>
class OpenGLManager;
class Shader;

class gameEngine {

public:
	gameEngine(float* deltaTime);
	~gameEngine();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
//Update Stuff
	void update();
	void glUpdate();
	void sdlUpdate();
//Render stuff
	void render(); // test what should be rendered
	void sdlRender(); // Render in SDL Window
	void glRender(); // Render Open GL window
	void clean();
	void openGL();
//Game State
	bool running() { return isRunning; };

//	void setDeltaTime(float dTime) { this->deltaTime = dTime; }
	//float getDeltaTime() { return deltaTime; }

	bool glRunning(){ return isGLRunning; };
	bool sdlRunning() { return isSDLRunning; };
//OpenGL stuff
	bool createGLWindow(int width, int height, int flags);
	bool createGLProgram(); // create shader/ vertex program
		//Shader
	Shader* createShader(const char* vertexShaderPath, const char* fragmentShaderPath); // This is to get by SDL_OpenGL wacky stuff
	void useShader(GLuint ID) { glUseProgram(ID); };

private:
	bool isRunning = false;
	bool isGLRunning = false;
	bool isSDLRunning = false;

	float* deltaTime;
//	GLuint gVBO = 0;
//	GLuint gIBO = 0;
//	GLuint gProgramID;
	//GLuint VAO;
	int cnt = 0;
	SDL_Window* window;
	SDL_Window* glWindow;
	SDL_GLContext glContext;
	SDL_Renderer* renderer;
	friend class OpenGLManager;
};






//#endif /^ gameEngine.h */
