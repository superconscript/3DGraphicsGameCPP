#pragma once
#include <SDL.h> // Input, Texture, Audio

// GL stuff
	#include <GL/glew.h>
	#include <SDL_opengl.h>
	#include <gl\GLU.h>
	#include "Shader.h"
//Else
#include "gameEngine.h"
#include "TextureManager.h" // for loading textures to use with opengl
// For storing road vertex
#include <vector>
// GLM
	#include <glm.hpp>
	#include <gtc/matrix_transform.hpp>
	#include <gtc/type_ptr.hpp>
// Camera Class
#include "Camera.h"

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
	void renderTriangle(GLuint VAO, GLuint VBO, GLuint EBO, GLuint gProgramID); // For when using Element Buffer
	void renderSquare(GLuint VAO, GLuint VBO);
	void generateRoad(GLfloat startPoint1X, GLfloat startPoint1Y, GLfloat startPoint1Z, GLfloat startPoint2X, GLfloat startPoint2Y, GLfloat startPoint2Z, GLfloat endPoint1X, GLfloat endPoint1Y, GLfloat endPoint1Z, GLfloat endPoint2X, GLfloat endPoint2Y, GLfloat endPoint2Z, int roadResolution, int distance);
	void generateRoad2(GLuint squares); //try 2 ( one column)
	void generateRoad3(GLuint gridWidth, GLuint gridLength, GLuint squareWidth, GLuint squareLength);
	void generateRoad4(GLuint gridWidth, GLuint gridLength, GLfloat squareWidth, GLfloat squareLength);
	//void generateRoad();
	void renderRoad();
	void renderRoad2(); // USed Mountain Shader
	void renderMovingTriangle(GLuint VAO, GLuint VBO);
	void renderMovingTriangleMat(GLuint VAO, GLuint VBO);
	//bool createGLWindow(int width, int height, int flags);
	
//
	void updateVBO(GLuint& gVBO, GLuint& VAO, GLfloat* vertices, int size);
	void updateVBO(GLuint& gVBO, GLuint& VAO, GLuint& EBO, GLfloat* vertices, int size, GLuint* indices, int indiceSize);
// CAMERA STUFF
	void updateCameraView(glm::vec3 newMatrix);
	void rotateCameraView(float angle, glm::vec3 vecAxis);
	//glm::mat4 getView();
private:
	int width = 800;
		int height = 600;
		float nearValue = 0.01f;
		float farValue = 300.0f;
	float timeValue = 0;
	//float timeDiff = 0;
	GLuint gProgramID;
//Window Stuff
	SDL_Window* glWindow;
	SDL_GLContext glContext;
// Game Camera
	Camera* gameCamera;
//Shaders
	Shader* triangleShader;
	Shader* squareShader;
	Shader* movingShader;
		UniformHolder* msColor;
		UniformHolder* msOffset;
		UniformHolder* msTransform;
		//Matrice Projection Uniform locations
		GLuint msModel;
		GLuint msProjection;
		GLuint msView;
	Shader* mountainShader;
		UniformHolder* mountColor;
		UniformHolder* mountOffset;
		UniformHolder* mountTransform;
		//Matrice Projection Uniform locations
		GLuint mountModel;
		GLuint mountProjection;
		GLuint mountView;
//////////
	gameEngine* gEngine; // the game engine
	bool isGLRunning = false;
	//GLint gVertextPos2dLocation = -1;

/// VBOs IBOS etc
		GLuint gVBO = 0;
		GLuint gIBO = 0;
		GLuint VAO;
		GLuint newVAO = -10;
		GLuint newVBO = 1;
		GLuint gEBO;
   ///Road Stuff
		GLuint roadVBO;
			// Vector to hold road information
				std::vector<GLfloat> roadVBOVECTOR;
		GLuint roadEBO;
			// Vector to hold Points
				std::vector<GLuint> roadIndices;
		GLuint roadVAO;
//Matrices for projection
		glm::mat4 transformMatrice = glm::mat4(1.0f);
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); // projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, nearValue, farValue); // projection matrix
		 //glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.3f, 0.0f));


	// States
	bool shaderInitSuccess;
	bool success;
	char infoLog[512];
	//SDL_Window* glWindow;
};

