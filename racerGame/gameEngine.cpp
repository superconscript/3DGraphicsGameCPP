#include "gameEngine.h"
#include "TextureManager.h" //  includes GameObject.h and Math.h
#include "KeyboardManager.h"
#include "MenuManager.h"
#include "OpenGLManager.h"
#include <stdio.h>
#include <iostream>

OpenGLManager* glManager;
//#include "KeyboardManager.h" // will now be included in PongPhysics.h
const int FPS = 120;
// Game Window settings
int gameWidth = 800;
int gameHeight = 600;
int flags;
const GLubyte* p;
KeyboardManager* keyMan;
// Menu Pointers
MenuManager* menuMan;
std::vector<menuItem*>* menuArray;

menuItem* testPtr;
menuItem* testPtr2;


//Start Menu Stuff
//Title Menu Item
textureMenuItem* titleMenuItem;

//Background Menu Item
textureMenuItem* backgroundMenuItem;
	const char* backgroundTex = "assets/rBackground.png";
	int bWidth = 520;
	int bHeight = 345;

//Start Button
textureStartButton* tStartButton;
	const char* startTex = "assets/start.png";
	int startWidth = 200;
	int startHeight = 125;

//Options Button
textureMenuItem* tOptionsButton;
	const char* optionsTex = "assets/options.png";
	int optionsWidth = 200;
	int optionsHeight = 125;


startButton* sB;
//Menu Colors
	SDL_Color menuColor1 = { 225,203,104,150 };
	SDL_Color menuColor2 = { 90,90,90,150 };
	SDL_Color menuMouseOverColor = { 60,60,170,150 };
	//const char* startTexture = "assets/go.png";

////////////////// Actual Engine ////////////////////////////////

gameEngine::gameEngine()
{}
gameEngine::~gameEngine()
{}

bool gameEngine::createGLWindow(int width, int height, int flags)
{
	char infoLog[512];
	glewExperimental = GL_TRUE;
	bool success = true;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	glWindow = SDL_CreateWindow("OPENGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	glContext = SDL_GL_CreateContext(glWindow);
	SDL_GL_MakeCurrent(glWindow, glContext);
	if (glContext == nullptr)
	{
		const char* msg = "OpenGL context could not be created: ";
		//	msg.append(SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Failed", msg, nullptr);
		isGLRunning = false;
	}
	else
	{
		glManager = new OpenGLManager(glWindow, this);
		/*
		GLenum glewError = glewInit();
		//	if(g != GLEW_)
		if (glewError != GLEW_OK) {
			success = false;
		}
		else {
			isGLRunning = true;
			p = glGetString(GL_VERSION);
			GLuint	gProgramID = glCreateProgram();
			//glManager->RenderSomething(gProgramID);
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			const GLchar* vertexShaderSource[] =
			{
				"#version 330 core\nlayout (location = 0) in vec3 aPos;\n void main()\n { gl_Position = vec4( aPos.x, aPos.y, aPos.z, 1.0); }\0"
			};
			//set vertex source
			glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
			// compile vertex source
			glCompileShader(vertexShader);

			//check vertex shader for errors
			GLint vShaderCompiled = GL_FALSE;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
			if (vShaderCompiled != GL_TRUE)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unable to compile vertex shader:", infoLog, nullptr);
				success = false;
			}
			else {
				// attach vertex shader to program
				glAttachShader(gProgramID, vertexShader);

				//create fragment shader
				GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

				//get fragment source
				const GLchar* fragmentShaderSource[] = { "#version 330 core\n out vec4 FragColor;\n void main()\n { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\0" };



				//set fragment source
				glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

				//Compile fragment source
				glCompileShader(fragmentShader);
				//check fragment shader for errors
				GLint fShaderCompiled = GL_FALSE;
				glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
				if (fShaderCompiled != GL_TRUE) {
					glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "couldn't compile the fragment shader", infoLog, nullptr);
					success = false;
				}
				else {
					// attach fragment shader to program

					glAttachShader(gProgramID, fragmentShader);

					//link program
					glLinkProgram(gProgramID);
					// check for errors
					GLint programSuccess = GL_TRUE;
					glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
					if (programSuccess != GL_TRUE)
					{
						glGetProgramInfoLog(gProgramID, 512, NULL, infoLog);
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "link Failed", infoLog, nullptr);
						success = false;
					}
					else {
						glClearColor(0.f, 0.5f, 0.f, 1.0f);
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						GLfloat vertices[] = {
							-0.5f, -0.5f, 0.0f,
							0.5f, -0.5f, 0.0f,
							0.0f, 0.5f, 0.0f
						};
						//Get vertex Attribute location
						GLuint VBO;
						glGenBuffers(1, &VBO);
						glBindBuffer(GL_ARRAY_BUFFER, VBO);
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

						glUseProgram(gProgramID); // Program with all our shaders
						glDeleteShader(vertexShader); // dont need them anymore
						glDeleteShader(fragmentShader); // dont need them anymore

						//GLuint VAO;
						glGenVertexArrays(1, &VAO);
						glBindVertexArray(VAO);

						glBindBuffer(GL_ARRAY_BUFFER, VBO);
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
						glEnableVertexAttribArray(0); // thats that


					//	if (gVertextPos2dLocation == -1)
					//	{
					//		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Failed", "LVertexPos2d is not a valid glsl progr variable", nullptr);
					//		success = false;
					//	}
					//	else
					//	{
							// initialize clear color
				
						glManager->renderTriangle(VAO, VBO, gProgramID);
						SDL_GL_SwapWindow(glWindow);
					}
				}
			}
		}
		*/
//createGLProgram();
		}
		return success;
	}
	
	Shader* gameEngine::createShader(const char* vertexShaderPath, const char* fragmentShaderPath) // create a shader
	{
		return new Shader(vertexShaderPath, fragmentShaderPath);
	
	}
	
bool gameEngine::createGLProgram() {
	GLenum err = glewInit();
	bool success = true;
	char infoLog[512];
	if (err != GLEW_OK) {
		//infoLog = <char*>(glGetString(GL_VERSION));
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "glewCreateGL Init Failure", reinterpret_cast<const char*>(glewGetErrorString(err)), NULL);
		success = false;
	}
	else {
		
	}
				



					isGLRunning = true;

			
		

		return success;
	//	SDL_GL_SwapWindow(glWindow);
	}
	



void gameEngine::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	 flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!.." << std::endl;
	//OpenGL STUFF

		//Old OpenGL stuff
		/*
	//	glWindow = SDL_CreateWindow("OPENGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		//glContext = SDL_GL_CreateContext(glWindow);
		if (glContext == nullptr)
		{
			std::string msg = "OpenGL context could not be created: ";
			msg.append(SDL_GetError());
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Failed", msg.c_str(), nullptr);
			isGLRunning = false;
		}
		else
		{
			glewInit();
			isGLRunning = true;
		}
		*/
	// SDL RENDERER STUFF
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isSDLRunning = true;
		isRunning = true;
	}
	menuMan = new MenuManager(width, height);
	menuArray = menuMan->getMenuArray();
// Start Game Menu
	//sB = menuMan->createStartButton(20, 20, 10, 10, &menuColor1, renderer, &menuColor2, false);
	double	screenW = width / 1;
	double screenH = height / 1;
	vector2d screenSize = { screenW, screenH};
	backgroundMenuItem = menuMan->createTextureMenuItem(100, 100, bWidth, bHeight, 0, 0, &menuColor1, renderer, backgroundTex, &menuColor2, false, screenSize);
	tStartButton = menuMan->createTextureStartButton(25, 15, startWidth, startHeight, 30, 30, &menuColor1, renderer, startTex, &menuColor2, false, screenSize);
	//tOptionsButton = menuMan->createTextureMenuItem(width / 2, height / 2, startWidth, startHeight, ((width / 2)), ((height / 2) - (height / 6)), &menuColor1, renderer, optionsTex, &menuColor2);
	tOptionsButton = menuMan->createTextureMenuItem(25, 15, optionsWidth, optionsHeight, 30, 50, &menuColor1, renderer, optionsTex, &menuColor2, false, screenSize);
	//Create our Players (which store the scores)
	// Create our Paddle's

	 //This is crashing, why?
	keyMan = new KeyboardManager(0);
	
}


void gameEngine::handleEvents() // Handles Keyboard Events, windows closing etc.
{
	//int c1 = player1->getControl();
	//int c2 = player2->getControl();
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			if (event.window.windowID == SDL_GetWindowID(glWindow)) { // If we're closing the OpenGL Window
				SDL_GL_DeleteContext(glContext);
				SDL_DestroyWindow(glWindow);
				glWindow = nullptr;
				
			}
			else if (event.window.windowID == SDL_GetWindowID(window)) { // if we're closing the SDL Window
				SDL_DestroyWindow(window);
				SDL_DestroyRenderer(renderer);
			}
		
		}
		if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
		//	int w = 50;
		//	int h = 50;
		//	int* w1 = nullptr;
		//	int* h1 = nullptr;
			if (event.window.windowID == SDL_GetWindowID(glWindow)) {
				// If its our openGL window;
			}
			else { // if it's our sdl window
				menuMan->Resize(SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h); // Having problem with object slicing
			}
		}


			// Get Input From Keyboard
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				// W key
			case SDLK_w: // FOR user using wasd
				keyMan->upKey();
				break;

				// A key
			case SDLK_a: // FOR user using wasd
				keyMan->leftKey();
				break;
				// S key
			case SDLK_s: // FOR user using wasd
				keyMan->downKey();
				break;
				// D key
			case SDLK_d: // FOR user using wasd
				keyMan->rightKey();
		
				break;



				//////////////////////////

				// KP 8 AKA UP
			case SDLK_KP_8: // FOR user using wasd
				keyMan->kpUpKey();
				break;
				// KP 4 AKA LEFT
			case SDLK_KP_4: // FOR user using wasd
				keyMan->kpLeftKey();
				break;
				// KP 2 AKA DOWN
			case SDLK_KP_2: // FOR user using wasd
				keyMan->kpDownKey();
				break;
				// KP 6 AKA RIGHT
			case SDLK_KP_6: // KP
				keyMan->kpRightKey();
				break;

			default:
				break;
			}
			break;
			/////////////////////////////////
	
		case SDL_KEYUP:
			switch (event.key.keysym.sym){
				 
						// W key
					case SDLK_w: // FOR user using wasd
						keyMan->upKeyUp();
						break;
						// A key
					case SDLK_a: // FOR user using wasd
						keyMan->leftKeyUp();
						break;
						// S key
					case SDLK_s: // FOR user using wasd
						keyMan->downKeyUp();
						break;
						// D key
					case SDLK_d: // FOR user using wasd
						keyMan->rightKeyUp();
						break;

						// KP 8 AKA UP
					case SDLK_KP_8: // FOR user using wasd
						keyMan->kpUpKeyUp();
						break;
						// KP 4 AKA LEFT
					case SDLK_KP_4: // FOR user using wasd
						keyMan->kpLeftKeyUp();
						break;
						// KP 2 AKA DOWN
					case SDLK_KP_2: // FOR user using wasd
						keyMan->kpDownKeyUp();
						break;
						// KP 6 AKA RIGHT
					case SDLK_KP_6: // KP
						keyMan->kpRightKeyUp();
						
						break;
					default:
						break;

					}
			break;
		case SDL_MOUSEMOTION: // Mouse moved
			break;
		case SDL_MOUSEBUTTONDOWN: //Mouse Click
			if (SDL_GetMouseFocus() == window) { // The SDL Window Is Taking Mouse Input
				//testPtr = menuMan->createMenuItem(100, 100, 0, 0, &menuMouseOverColor, renderer, &menuColor2, false, menuMan->getScreenSize());
				// Now we need to check which menu Was pressed
				int x, y;
				SDL_GetMouseState(&x, &y);
				menuItem* clickedMenu = menuMan->getMenuFromCoordinates(x, y);
				clickedMenu->changeColor(&menuMouseOverColor);
				clickedMenu->clicked(); //Will add this function
				
			}
			else if (SDL_GetMouseFocus() == glWindow) { // The OpenGl Window Is Taking Mouse Input
				//testPtr2 = menuMan->createMenuItem(100, 100, 0, 0, &menuColor1, renderer, &menuColor2, false, menuMan->getScreenSize());
			}
			break;

		default:
			break;

	}
}

GLfloat newVertices[] = {	
	//position		//color
	
	//Sky
//Left triangle
	-1.0f, 1.0f, 0.0f,	 0.2f, 0.2f, 0.9f, // top Left
   -1.0f, 0.0f, 0.0f,	 0.4f, 0.2f, 0.2f, //bottom left
	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f, 0.0f, //bottom right
//Right triangle
	1.0F, 1.0f, 0.0f,	0.2f, 0.2f, 0.9f,	// top right
	//1.0f, -1.0f, 0.0f,	 0.4f, 0.2f, 0.2f//,
	//0.0f, 1.8f, 0.0f,	 0.0f, 0.0f, 0.0f 
};
GLuint squareIndices[6]{
// Sky
	0, 1, 2, // Left triangle
	0, 2, 3 // Right triangle
// Road

};
GLuint EBO;
//glGenBuffers(1, &EBO); Since we're sending it we dont need it

GLuint newVAO = 0;
GLuint newVBO = 0;
int updateCounter{ 0 };
glm::vec3 rotationAxis = glm::vec3(0.0f, 0.5f, 0.0f);
float zoomSensitivity = 0.04f;
float moveSensitivity = 0.01f;
float angleSensitivity = 5.0f;
void gameEngine::glUpdate() { // Handle our OpenGL update
	//glManager->renderTriangle(VAO, gVBO, gProgramID);
	if (updateCounter == 200) {
		//glManager->updateVBO(newVBO, newVAO, EBO, newVertices, sizeof(newVertices), squareIndices, sizeof(squareIndices));
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "update vertices", "vertices have been updated", NULL);
		//glManager->generateRoad(-1.0f, 0.8f, -0.5f, 1.0f, 0.8f, -0.5f, -0.7f, 0.0f, 5.1f, 0.4f, 0.0f, 5.1f, 20, 100);	
		//						x1   y1     z1     x2     y2     z2    xf1   yf1   zf1    xf2   yf2   zf2  res   distance
		//glManager->generateRoad2(100);
		//glManager->generateRoad3(20, 20, 1, 1); works but rows aren't yet optimised
		glManager->generateRoad4(200, 200, 0.1f, 0.1f); // doesn't work yet... UPDATE It Seems to work
	}
// Camera Movement Update
	if (keyMan->getKeyValue(0) == 1) { 
		glManager->updateCameraView(glm::vec3(0.0f, -1 * moveSensitivity, 0.0f));
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Key pressed", "should've moved up", NULL);
	}
	if (keyMan->getKeyValue(1) == 1) {
		glManager->updateCameraView(glm::vec3(0.0f, 0.0f, zoomSensitivity));
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Key pressed", "should've moved in", NULL);
	}
	if (keyMan->getKeyValue(2) == 1) {
		glManager->updateCameraView(glm::vec3(moveSensitivity, 0.0f, 0.0f));
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Key pressed", "should've moved left", NULL);
	}
	if (keyMan->getKeyValue(3) == 1) {
		glManager->rotateCameraView(angleSensitivity, rotationAxis);
		//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Key pressed", "should've turned left", NULL);
	}
	if (keyMan->getKeyValue(4) == 1) {
		glManager->updateCameraView(glm::vec3(-1 * moveSensitivity, 0.0f, 0.0f));
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Key pressed", "should've moved right", NULL);
	}
	if (keyMan->getKeyValue(5) == 1) {
		glManager->rotateCameraView(-1 * angleSensitivity, rotationAxis);
		//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Key pressed", "should've turned right", NULL);
	}
	if (keyMan->getKeyValue(6) == 1) {
		glManager->updateCameraView(glm::vec3(0.0f, moveSensitivity, 0.0f));
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Key pressed", "should've moved down", NULL);
	}
	if (keyMan->getKeyValue(7) == 1) {
		glManager->updateCameraView(glm::vec3(0.0f, 0.0f, -1 * zoomSensitivity));
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Key pressed", "should've moved out", NULL);
	}

	updateCounter++;
}



bool bootedGL = false;
bool failedBoot = false;
void gameEngine::sdlUpdate() { // Handle SDL udpate stuff
	//SDL_RaiseWindow(window);
	if (bootedGL == false) {
		for (auto v : *menuArray) {
			if (v->isStarted() == true) {
				bootedGL = true;
				if (failedBoot == false) {
					bool glWindowSuccess = createGLWindow(gameWidth, gameHeight, flags);

					if (glWindowSuccess == true) {
						//glClearColor(0.2f, 0.4f, 0.5f, 1.0f);
						//glClear(GL_COLOR_BUFFER_BIT);
						createGLProgram();
						
				//	glManager->RenderSomething(glWindow);
						SDL_RaiseWindow(glWindow);
					}

					else {
						bootedGL = false;
						failedBoot = true;
					}
				}
				 //glGetString(GL_VERSION);
			
				
			}
		}
	}
	else {
		isSDLRunning = false;
	}
}
//int counter = 0;
//float time;
//std::string frames;
void gameEngine::update() // Update Handler (controls whether to update SDL or OpenGL depending on which is running)
{
	/*
	if (counter == 500)
	{
	//	 frames = std::to_string((SDL_GetTicks() - time) / 1000);
		 SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Frames", frames.c_str(), NULL);
	}
	*/
	//time = SDL_GetTicks();
	if (isRunning == false) {
		clean();
	}
	if (isGLRunning == true) {
		this->glUpdate();
}
	if (isSDLRunning == true) {
		this->sdlUpdate();
	}
	else {
		SDL_DestroyWindow(window);
	}
	//counter++;
	//time = SDL_GetTicks();
}

void gameEngine::sdlRender() // Rendering for SDL Window
{
	SDL_RenderClear(renderer);
	//player->Render(); //Render the Character
 // Render our paddles
	//backgroundMenuItem->Render();
	for (auto val : *menuArray) { // Render all our menu's
	//	val->Render();
		val->Render();
	//	tmpPtr->Render();
		
	}

	
	//sB->Render();
	SDL_RenderPresent(renderer);
}


void gameEngine::glRender() // Rendering for OPENGL
{

//	SDL_GL_SwapWindow(glWindow);
	//glManager->renderTriangle();
	//glClearColor(0.f, 0.5f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glManager->renderTriangle(newVAO, newVBO, EBO, gProgramID);
	//glManager->renderMovingTriangleMat(newVAO, newVBO);

	//glManager->renderRoad();

	glManager->renderRoad2();

	//glManager->renderMovingTriangle(newVAO, newVBO);
}

void gameEngine::render() { // Rendering handler
	if (isGLRunning == true) {
		glRender();
	}
	if (isSDLRunning == true) {
		sdlRender();
	}
}


void gameEngine::clean()
{
	//SDL_DestroyWindow(window);
	//SDL_DestroyRenderer(renderer);
	SDL_Quit();
}