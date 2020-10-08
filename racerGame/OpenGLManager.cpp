#include "OpenGLManager.h"

//Static objects in game: Sky;
	


OpenGLManager::OpenGLManager(SDL_Window* glWindow, gameEngine* gameEngine, float* deltaTime ) {
	glewInitialize();
	this->glWindow = glWindow;
	this->gEngine = gameEngine;
	this->deltaTime = deltaTime;
//	initShaders();
	this->shaderInitSuccess = true;
	triangleShader = this->gEngine->createShader("shaders/shader.vs", "shaders/shader.fs");
	if (triangleShader == nullptr) {
		this->shaderInitSuccess = false;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TraingleShader init fail", "couldn't make it", NULL);
	}
	//squareShader = this->gEngine->createShader("shaders/squareShader.vs", "shaders/squareShader.fs");
	//if (triangleShader == nullptr) {
	//	this->shaderInitSuccess = false;
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SquareShader init fail", "couldn't make it", NULL);
	//}
	movingShader = this->gEngine->createShader("shaders/movingShader.vs", "shaders/movingShader.fs");
	if (movingShader == nullptr) {
		this->shaderInitSuccess = false;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "MovingShader init fail", "couldn't make it", NULL);
	}
	else { // initialize uniform positions	//color = passedColor || offset = positionOffset;
		msColor = new UniformHolder(movingShader->ID, glGetUniformLocation(movingShader->ID, "passedColor"));
		//msOffset = new UniformHolder(movingShader->ID, glGetUniformLocation(movingShader->ID, "positionOffset")); Replaced with matrice;
	// Initialize matrices
		msTransform = new UniformHolder(movingShader->ID, glGetUniformLocation(movingShader->ID, "transform"));
		//msModel = glGetUniformLocation(movingShader->ID, "transform");
		msView = glGetUniformLocation(movingShader->ID, "view");
		msProjection = glGetUniformLocation(movingShader->ID, "projection");
	}
//Mountain Shader
	mountainShader = this->gEngine->createShader("shaders/mountainShader.vs", "shaders/mountainShader.fs");
	if (mountainShader == nullptr) {
		this->shaderInitSuccess = false;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "MovingShader init fail", "couldn't make it", NULL);
	}
	else { // initialize uniform positions	//color = passedColor || offset = positionOffset;
		mountColor = new UniformHolder(mountainShader->ID, glGetUniformLocation(mountainShader->ID, "passedColor"));
		//msOffset = new UniformHolder(movingShader->ID, glGetUniformLocation(movingShader->ID, "positionOffset")); Replaced with matrice;
	// Initialize matrices
		mountTransform = new UniformHolder(mountainShader->ID, glGetUniformLocation(mountainShader->ID, "transform"));
		//msModel = glGetUniformLocation(movingShader->ID, "transform");
		mountView = glGetUniformLocation(mountainShader->ID, "view");
		mountProjection = glGetUniformLocation(mountainShader->ID, "projection");
	}


//	GLfloat initVertices[] = {
	//	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 1.0f,
	//	0.5f, 0.0f, 0.0f,	0.0f, 0.0f, 0.5f,
	//	-0.5f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f
	//};
	glEnable(GL_DEPTH_TEST);
	//newVAO = 1;
	//newVBO = 1;
	//updateVBO(newVBO, newVAO, initVertices, sizeof(initVertices) );
	//this->gameCamera = new Camera(this->deltaTime);
	
	this->gameCamera = new Camera(this->deltaTime, 5.0f, glm::vec3(15,10,0));
}
OpenGLManager::~OpenGLManager() {

}
/*
void OpenGLManager::initShaders() {
	this->shaderInitSuccess = true;
	Shader* triangleShader = this->gEngine->createShader("shaders/shader.vs", "shaders/shader.fs");
	if (triangleShader == nullptr) {
		this->shaderInitSuccess = false;

	}
	Shader* 
}
*/
bool OpenGLManager::RenderSomething(SDL_Window* glWindow) {
	return success;
}



void OpenGLManager::updateVBO (GLuint &gVBO, GLuint &VAO, GLfloat* vertices, int size ) {
	/*
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &gVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Position Attributes
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Color attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	*/
////////////////////
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 //VERTICES
	/*
	GLfloat vertices[] = {
		//position				//colors
		0.5f, -0.5f, 0.0f,	 1.0f, 0.0f, 0.0f, // botom right
	   -0.5f, -0.5f, 0.0f,	 0.0f, 1.0f, 0.0f, //bottom left
		0.0f, 0.5f, 0.0f,	 0.0f, 0.0f, 1.0f //top
	};
	*/

	//Get vertex Attribute location
	//GLuint VBO;
	glGenBuffers(1, &gVBO);
	//	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//	glUseProgram(gProgramID); // Program with all our shaders
	//	glDeleteShader(vertexShader); // dont need them anymore
	//	glDeleteShader(fragmentShader); // dont need them anymore

		//GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);


	//Position Attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Color attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



///////////////

	//glBindVertexArray(0);

	//glGenVertexArrays(1, &VAO);

	
	}

void OpenGLManager::updateVBO(GLuint& gVBO, GLuint& VAO, GLuint& EBO, GLfloat* vertices, int size, GLuint* indices, int indiceSize) {
	glClearColor(0.f, 0.5f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//VERTICES
	   /*
	   GLfloat vertices[] = {
		   //position				//colors
		   0.5f, -0.5f, 0.0f,	 1.0f, 0.0f, 0.0f, // botom right
		  -0.5f, -0.5f, 0.0f,	 0.0f, 1.0f, 0.0f, //bottom left
		   0.0f, 0.5f, 0.0f,	 0.0f, 0.0f, 1.0f //top
	   };
	   */

	   //Get vertex Attribute location
	   //GLuint VBO;
	glGenBuffers(1, &gVBO);
	glGenBuffers(1, &EBO);
	//	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	//	glUseProgram(gProgramID); // Program with all our shaders
	//	glDeleteShader(vertexShader); // dont need them anymore
	//	glDeleteShader(fragmentShader); // dont need them anymore

		//GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	// Element array buffer	EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize, indices, GL_STATIC_DRAW);

	//Position Attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Color attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}


	void OpenGLManager::renderTriangle(GLuint VAO, GLuint VBO, GLuint gProgramID) {
			if (this->triangleShader == nullptr) {
				this->shaderInitSuccess = false;
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TraingleShader init fail", "couldn't make it", NULL);
			}
			else {
				triangleShader->use();
				//frameRate = SDL_GetTicks() - this->timeValue;
				int timeDiff = SDL_GetTicks();
				float greenValue = sin(timeDiff / 500) / 2.0f + 0.5f;
				float redValue = (sin(timeDiff / 2.0f) + .9f);



				//	glUseProgram(gProgramID);
				//	int vertexColorLocation = glGetUniformLocation(gProgramID, "ourColor");
					//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
			
					glBindVertexArray(VAO);
				
				glDrawArrays(GL_TRIANGLES, 0, 6);
				SDL_GL_SwapWindow(glWindow);
				//	counter++;
				this->timeValue = SDL_GetTicks() / 1000;
			}
	}

	void OpenGLManager::renderTriangle(GLuint VAO, GLuint VBO, GLuint EBO, GLuint gProgramID) {
		if (this->triangleShader == nullptr) {
			this->shaderInitSuccess = false;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TraingleShader init fail", "couldn't make it", NULL);
		}
		else {
			triangleShader->use();
			//frameRate = SDL_GetTicks() - this->timeValue;
			float timeDiff = SDL_GetTicks();
			float greenValue = sin(timeDiff / 500) / 2.0f + 0.5f;
			float redValue = (sin(timeDiff / 2.0f) + .9f);



			//	glUseProgram(gProgramID);
			//	int vertexColorLocation = glGetUniformLocation(gProgramID, "ourColor");
				//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

			glBindVertexArray(VAO);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			SDL_GL_SwapWindow(glWindow);
			//	counter++;
			this->timeValue = SDL_GetTicks() / 1000;
		}
	}

	void OpenGLManager::renderSquare(GLuint VAO, GLuint VBO) {
		if (this->squareShader == nullptr) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SquareShader init fail", "couldn't make it", NULL);
		}
		else {
			squareShader->use();

			glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIA)
		}
	}
//glWindow = SDL_CreateWindow("OPENGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	//bool OpenGLManager::createGLWindow(int width, int height, int flags)
	/*{
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
		SDL_Window* glWindow = SDL_CreateWindow("OPENGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		SDL_GLContext glContext = SDL_GL_CreateContext(glWindow);
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
			GLenum glewError = glewInit();
			//	if(g != GLEW_)
			if (glewError != GLEW_OK) {
				success = false;
			}
			else {
				isGLRunning = true;
				//p = glGetString(GL_VERSION);
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

							renderTriangle(VAO, VBO, gProgramID);
							SDL_GL_SwapWindow(glWindow);
						}
					}
				}
			}

		}*/
////		return success;
	//}

void OpenGLManager::renderMovingTriangle(GLuint VAO, GLuint VBO) {
	if (this->movingShader == nullptr) {
		this->shaderInitSuccess = false;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "MovingShader render fail", "couldn't make it", NULL);
	}
	float x, y, z;
	float r, g, b;
	int time = SDL_GetTicks();
	x = sin(time / 100);
	y = sin(time / 200);
	z = 0;

	r = (sin(time / 300) / 2.0f) + 0.5f;
	g = (sin(time / 700) / 2.0f) + 0.5f;
	b = (sin(time / 200) / 2.0f) + 0.5f;

	movingShader->use();
	// Position = location 0 || Color = location 1; || positionOffset = location 2;
	glUniform3f(msOffset->location, x, y, z); // set pos
	glUniform4f(msColor->location, r, g, b, 1.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	SDL_GL_SwapWindow(glWindow);
	}

// Using Matrices
void OpenGLManager::renderMovingTriangleMat(GLuint VAO, GLuint VBO) {
	if (this->movingShader == nullptr) {
		this->shaderInitSuccess = false;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "MovingShader render fail", "couldn't make it", NULL);
	}
	float x, y, z;
	float r, g, b;
	glm::mat4 transformMatrice = glm::mat4(1.0f); // Initialize to identity
	

	int time = SDL_GetTicks();
	x = sin(time / 1000);
	y = sin(time / 200);
	z = 0;

	r = (sin(time / 300) / 2.0f) + 0.5f;
	g = (sin(time / 700) / 2.0f) + 0.5f;
	b = (sin(time / 200) / 2.0f) + 0.5f;
//Matrices
	transformMatrice = glm::translate(transformMatrice, glm::vec3(0.5, 0.5f, 0.0f));
	transformMatrice = glm::rotate(transformMatrice, x * glm::radians(-44.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); // projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//	glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
   //////////
	movingShader->use();
	// Position = location 0 || Color = location 1; || positionOffset = location 2;
// Set Uniform Matrices
	glUniformMatrix4fv(msTransform->location,1, GL_FALSE, glm::value_ptr(transformMatrice)); // set pos
	glUniformMatrix4fv(msView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(msProjection, 1, GL_FALSE, glm::value_ptr(projection));
	//glUniformMatrix4fv(msView, 1, GL_FALSE, glm::value_ptr(ortho));


	glUniform4f(msColor->location, r, g, b, 1.0f);
	//glUniformMatrix4fv()
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	SDL_GL_SwapWindow(glWindow);
}
// We will use vector to store vertices		Higher resolution for more accurate curves
void OpenGLManager::generateRoad(GLfloat startPoint1X, GLfloat startPoint1Y, GLfloat startPoint1Z, GLfloat startPoint2X, GLfloat startPoint2Y, GLfloat startPoint2Z, GLfloat endPoint1X, GLfloat endPoint1Y, GLfloat endPoint1Z, GLfloat endPoint2X, GLfloat endPoint2Y, GLfloat endPoint2Z, int roadResolution, int distance) {
	// Lets calculate the vertices to pass to the VBO;
			// First lets calculate DeltaX and Delta Y for each point
				// We can guestimate the actual distance by approximation of the distance between each point
	// For now we'll make color fixed;

	//COLORS
	const GLfloat	redValue = 0.2f;
	const GLfloat	greenValue = 0.5f;
	const GLfloat	blueValue = 0.2f;


	int numberOfPoints = 4 + (2 * roadResolution);
	float numberOfTriangles = 2 + (roadResolution * 2);
	// In our VBO it's: 3 floats for position, 3 floats for color;

	GLfloat deltaX1 = endPoint1X - startPoint1X;
	GLfloat deltaY1 = endPoint1Y - startPoint1Y;
	GLfloat deltaZ1 = endPoint1Z - startPoint1Z;


	GLfloat deltaX2 = endPoint2X - startPoint2X;
	GLfloat deltaY2 = endPoint2Y - startPoint2Y;
	GLfloat deltaZ2 = endPoint2Z - startPoint2Z;



	/*
	Our Vector will be ordered like this (storing points)		Resolution is number of squares
		Square 1 ( 2 + 2N vertices per Square, 2 Triangles per Square, 6 + 6N (x and y and z coordinates)
				triangle1
				P0, P1, P2
					X0, Y0, X1,Y1, X2, Y2,
				triangle2
				P1, P2, P3
					X3, Y3
		Etc.

	*/
	//GENERATE VBO
		//Vertex
		//roadVBOVECTOR.push_back(startPoint1X); // Set initial value
		//roadVBOVECTOR.push_back(startPoint1Y);
		//roadVBOVECTOR.push_back(startPoint1Z);
			// Color (R, G , B)
			////	roadVBOVECTOR.push_back(redValue);
			//	roadVBOVECTOR.push_back(greenValue);
			//	roadVBOVECTOR.push_back(blueValue);
		//Vertex
		//roadVBOVECTOR.push_back(startPoint2X); // Set initial value
		//roadVBOVECTOR.push_back(startPoint2Y);
		//roadVBOVECTOR.push_back(startPoint2Z);
			// Color
	float lerpTool = 1 / roadResolution;
	//double i = 0;
	for (GLuint i = 0; i <= roadResolution; i++) {
		// Lerp From first initial point
		roadVBOVECTOR.push_back(startPoint1X + (deltaX1 * (float)i * lerpTool));
		roadVBOVECTOR.push_back(startPoint1Y + (deltaY1 * (float)i * lerpTool));
		roadVBOVECTOR.push_back(startPoint1Z + (deltaZ1 * (float)i * lerpTool));
		roadVBOVECTOR.push_back(redValue);
		roadVBOVECTOR.push_back((sin(i) / 2) + .5); // add some variance
		roadVBOVECTOR.push_back(blueValue);
		// LERP from second initial point
		roadVBOVECTOR.push_back(startPoint2X + (deltaX2 * i * lerpTool));
		roadVBOVECTOR.push_back(startPoint2Y + (deltaY2 * i * lerpTool));
		roadVBOVECTOR.push_back(startPoint2Z + (deltaZ2 * i * lerpTool));
		roadVBOVECTOR.push_back(redValue);
		roadVBOVECTOR.push_back(greenValue);
		roadVBOVECTOR.push_back(blueValue);

		//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "THE ROAD GENERATION", "count em up", NULL);
				// start + (deltaX * i / resolution)	LERP	when i = 0 its just initial


	}
	//Generate IBO for our VBO
	int backPoint = 3; // 3 points to a triangle
	for (GLuint i = 0; i < numberOfTriangles; i++) {



		for (GLuint j = 0; j < 3 + i; j++) {	// 0 , 1 , 2 | 1, 2 ,3 | 2, 3, 4 | 3, 4, 5

		//	if (i == backPoint) {
			//	backPoint = backPoint + 1;
		//		i = i - 2;
		//	}
			// for every three we need to decrement by 2

			this->roadIndices.push_back(j);
			//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "THE INDICE GENERATION", "INDICE em up", NULL);
		}

	}
	//TEST
	/*
	this->roadIndices.push_back(0);
	this->roadIndices.push_back(1);
	this->roadIndices.push_back(2);
	this->roadIndices.push_back(1);
	this->roadIndices.push_back(2);
	this->roadIndices.push_back(3);
	this->roadIndices.push_back(2);
	this->roadIndices.push_back(3);
	this->roadIndices.push_back(4);
	*/
	glGenBuffers(1, &this->roadVBO); // controls our vertice information
	glGenBuffers(1, &this->roadEBO); // tells us how to render the quads

// GEN and BIND our VAO
	glGenVertexArrays(1, &this->roadVAO);
	glBindVertexArray(this->roadVAO);
	// Bind our VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->roadVBO);
	glBufferData(GL_ARRAY_BUFFER, roadVBOVECTOR.size() * sizeof(GLfloat), roadVBOVECTOR.data(), GL_DYNAMIC_DRAW);
	// Bind our Index / Element stuff
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->roadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->roadIndices.size() * sizeof(GLuint), roadIndices.data(), GL_DYNAMIC_DRAW);

	// VBO attributes (position and color)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//for (GLuint x = 0; x < roadVBOVECTOR.size(); x++) {
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "ROAD VBO Number", "COUNT THE VBO em up", NULL);
	//}

	//for (GLuint x = 0; x < roadIndices.size(); x++) {
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "ROAD INDICE Number", "COUNT THE INDICE em up", NULL);
//	}
// DONE

}
		
/*		//Lets rebuild this func.
void OpenGLManager::generateRoad2( GLuint squares) {

	GLuint x, y, z;
	float redValue = 0.5f;
	float greenValue = 0.1f;
	float blueValue = 0.9f;
	GLuint triangles = squares * 2;
	int vertexCounter;
	// Lets create a square
	// indices = squares * 3;
	for (x = 0; x < squares; x++) {
		for (y = 0; y < (triangles); y++) {

			for (z = 0; z < 3; z++) { // 3 points in triangle
				// 4 Vertices for square, 6 indices
		//Left Side
				float zValue = -1 * (y - 10 + (x * 10);

				roadVBOVECTOR.push_back(-1); //x
				roadVBOVECTOR.push_back(0.5f);
				roadVBOVECTOR.push_back(zValue);
				//Color
				roadVBOVECTOR.push_back(redValue);
				roadVBOVECTOR.push_back(greenValue);
				roadVBOVECTOR.push_back(blueValue);
		//Right Side
				roadVBOVECTOR.push_back(1); //x
				roadVBOVECTOR.push_back(0.5f);
				roadVBOVECTOR.push_back(zValue);
				//Color
				roadVBOVECTOR.push_back(redValue);
				roadVBOVECTOR.push_back(greenValue * sin(((float)y) / 2));
				roadVBOVECTOR.push_back(blueValue);


				//Indices


				roadIndices.push_back(y + z); // 4 need 2 more

			}
			// indices come in sets of 3
		}
	}
// Lets do our indices


	// We need to create the EBO

// Actual Buffer Stuff;
	glGenBuffers(1, &this->roadVBO); // controls our vertice information
	glGenBuffers(1, &this->roadEBO); // tells us how to render the quads

// GEN and BIND our VAO
	glGenVertexArrays(1, &this->roadVAO);
	glBindVertexArray(this->roadVAO);
	// Bind our VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->roadVBO);
	glBufferData(GL_ARRAY_BUFFER, roadVBOVECTOR.size() * sizeof(GLfloat), roadVBOVECTOR.data(), GL_DYNAMIC_DRAW);
	// Bind our Index / Element stuff
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->roadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->roadIndices.size() * sizeof(GLuint), roadIndices.data(), GL_DYNAMIC_DRAW);

	// VBO attributes (position and color)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
		}
*/
	// Alt try

//generateRoad2
/*
void OpenGLManager::generateRoad2(GLuint squares) {

	GLuint x, y, z;
	float redValue = 0.5f;
	float greenValue = 0.1f;
	float blueValue = 0.9f;
	GLuint triangles = squares * 2;
//	int vertexCounter;
	int initialZ = 0;
	int zStep = 1;
	// Lets create a square
	// indices = squares * 3;
	// Initial 2 points no matter what
		
	for (x = 0; x <= squares; x++) { // x = 0 is the initial 2 points
	//	float zValue = -1 * (x * 10);
		float zValue = initialZ + (zStep * x);
		// 2 points per square
	//Left Side
		roadVBOVECTOR.push_back(-1); //x
		//roadVBOVECTOR.push_back(0.0f);
		roadVBOVECTOR.push_back(sin(x));
		roadVBOVECTOR.push_back(-1 * zValue);
		//Color
		roadVBOVECTOR.push_back(redValue);
	//	roadVBOVECTOR.push_back(greenValue);
		roadVBOVECTOR.push_back(((float)x) / ((float)squares));
		roadVBOVECTOR.push_back(blueValue);
	
	//Right Side
		roadVBOVECTOR.push_back(1); //x
		//roadVBOVECTOR.push_back(0.0f);
		roadVBOVECTOR.push_back(0.0f);
		roadVBOVECTOR.push_back(-1 * zValue);
		//Color
		roadVBOVECTOR.push_back(redValue);
		roadVBOVECTOR.push_back( ((float)x) / ((float)squares));
		roadVBOVECTOR.push_back(blueValue);
/*
		for (y = 0; y < (triangles); y++) {

			for (z = 0; z < 3; z++) { // 3 points in triangle
				// 4 Vertices for square, 6 indices
		//Left Side
		

				roadVBOVECTOR.push_back(-1); //x
				roadVBOVECTOR.push_back(0.5f);
				roadVBOVECTOR.push_back(zValue);
				//Color
				roadVBOVECTOR.push_back(redValue);
				roadVBOVECTOR.push_back(greenValue);
				roadVBOVECTOR.push_back(blueValue);
				//Right Side
				roadVBOVECTOR.push_back(1); //x
				roadVBOVECTOR.push_back(0.5f);
				roadVBOVECTOR.push_back(zValue);
				//Color
				roadVBOVECTOR.push_back(redValue);
				roadVBOVECTOR.push_back(greenValue * sin(((float)y) / 2));
				roadVBOVECTOR.push_back(blueValue);


				//Indices


				//roadIndices.push_back(y + z); // 4 need 2 more

			}
			// indices come in sets of 3
		}
		
	}
	// Lets do our indices
	for (int j = 0; j < triangles; j++) {
		// for each triangle
		for (int k = 0; k < 3; k++) { // triangle has 3 points
			roadIndices.push_back(j + k);
		}
	}

		// We need to create the EBO

	// Actual Buffer Stuff;
	glGenBuffers(1, &this->roadVBO); // controls our vertice information
	glGenBuffers(1, &this->roadEBO); // tells us how to render the quads

// GEN and BIND our VAO
	glGenVertexArrays(1, &this->roadVAO);
	glBindVertexArray(this->roadVAO);
	// Bind our VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->roadVBO);
	glBufferData(GL_ARRAY_BUFFER, roadVBOVECTOR.size() * sizeof(GLfloat), roadVBOVECTOR.data(), GL_DYNAMIC_DRAW);
	// Bind our Index / Element stuff
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->roadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->roadIndices.size() * sizeof(GLuint), roadIndices.data(), GL_DYNAMIC_DRAW);

	// VBO attributes (position and color)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

*/

// Generate Road In Grid
//generateRoad3
/*
void OpenGLManager::generateRoad3(GLuint gridWidth, GLuint gridLength, GLuint squareWidth, GLuint squareLength) {

	GLuint x, y, z;
	float redValue = 0.5f;
	float greenValue = 0.1f;
	float blueValue = 0.9f;
	GLuint triangles = gridWidth * gridLength * 2;
	GLuint trianglesInRow = gridLength * 2;
	//	int vertexCounter;
	int initialZ = 0;
	int zStep = squareLength;
	int colorStep = 10;
	// Lets create a square
	// indices = squares * 3;
	// Initial 2 points no matter what
	for (x = 0; x <= gridWidth; x++) {
		for (y = 0; y <= gridLength; y++) { // x = 0 is the initial 2 points
		//	float zValue = -1 * (x * 10);
			float zValue = initialZ + (zStep * y);
			float yValue = (sin(y) * 10);
			// 2 points per square
		//Left Side
			roadVBOVECTOR.push_back((squareWidth * x)); //x
			//roadVBOVECTOR.push_back(0.0f);
			roadVBOVECTOR.push_back(sin(y));
			roadVBOVECTOR.push_back(-1 * zValue);
			//Color
			//roadVBOVECTOR.push_back(redValue);
			roadVBOVECTOR.push_back(  ( (float) ((int) yValue % colorStep) )  /  colorStep);
			//	roadVBOVECTOR.push_back(greenValue);
			roadVBOVECTOR.push_back(((float)x) / ((float)gridLength));
			roadVBOVECTOR.push_back(blueValue);

		//Right Side
			roadVBOVECTOR.push_back((squareWidth * (x + 1))); //x
			//roadVBOVECTOR.push_back(0.0f);
			roadVBOVECTOR.push_back(0.0f);
			roadVBOVECTOR.push_back(-1 * zValue);
			//Color
			//roadVBOVECTOR.push_back(redValue);
			roadVBOVECTOR.push_back(((float)( (int) yValue % colorStep)) / colorStep);
			roadVBOVECTOR.push_back(((float)x) / ((float)gridLength));
			roadVBOVECTOR.push_back(blueValue);
			/*
					for (y = 0; y < (triangles); y++) {

						for (z = 0; z < 3; z++) { // 3 points in triangle
							// 4 Vertices for square, 6 indices
					//Left Side


							roadVBOVECTOR.push_back(-1); //x
							roadVBOVECTOR.push_back(0.5f);
							roadVBOVECTOR.push_back(zValue);
							//Color
							roadVBOVECTOR.push_back(redValue);
							roadVBOVECTOR.push_back(greenValue);
							roadVBOVECTOR.push_back(blueValue);
							//Right Side
							roadVBOVECTOR.push_back(1); //x
							roadVBOVECTOR.push_back(0.5f);
							roadVBOVECTOR.push_back(zValue);
							//Color
							roadVBOVECTOR.push_back(redValue);
							roadVBOVECTOR.push_back(greenValue * sin(((float)y) / 2));
							roadVBOVECTOR.push_back(blueValue);


							//Indices


							//roadIndices.push_back(y + z); // 4 need 2 more

						}
						// indices come in sets of 3
					}
					
		}
}
	// Lets do our indices
	//vertices in row = gridLength *2

	for (GLuint j = 0; j < triangles; j++) {
		// for each triangle
		for (int k = 0; k < 3; k++) { // triangle has 3 points
			roadIndices.push_back(j + k);
		}
	}

//New Way
		//for (GLuint i = 0; i < gridWidth; i++) { // which row we're in

//	}
	//}
	// We need to create the EBO

// Actual Buffer Stuff;
	glGenBuffers(1, &this->roadVBO); // controls our vertice information
	glGenBuffers(1, &this->roadEBO); // tells us how to render the quads

// GEN and BIND our VAO
	glGenVertexArrays(1, &this->roadVAO);
	glBindVertexArray(this->roadVAO);
	// Bind our VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->roadVBO);
	glBufferData(GL_ARRAY_BUFFER, roadVBOVECTOR.size() * sizeof(GLfloat), roadVBOVECTOR.data(), GL_DYNAMIC_DRAW);
	// Bind our Index / Element stuff
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->roadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->roadIndices.size() * sizeof(GLuint), roadIndices.data(), GL_DYNAMIC_DRAW);

	// VBO attributes (position and color)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
} 
// creates grid, however edge of rows are messed up since it creates duplicate vertices 


*/

//Generate road to grid Row Fix attempt (Works but there's memory leak)
void OpenGLManager::generateRoad4(GLuint gridWidth, GLuint gridLength, GLfloat squareWidth, GLfloat squareLength) {

	GLuint x, y, z;
	float redValue = 0.5f;
	float greenValue = 0.1f;
	float blueValue = 0.9f;
	GLuint triangles = gridWidth * gridLength * 2;
	GLuint trianglesInRow = gridLength * 2;
	//	int vertexCounter;
	GLuint initialZ = 0;
	GLfloat zStep = squareLength;
	GLuint colorStep = 100;
	// Lets create a square
	// indices = squares * 3;
	// Initial 2 points no matter what
	for (x = 0; x < gridWidth * 2; x++) {
		for (y = 0; y <= gridLength; y++) { // x = 0 is the initial 2 points
		//	float zValue = -1 * (x * 10);
			float zValue = initialZ + (zStep * y);
			float yValue = (sin(y) * 10);
			float randSeed = (rand() * SDL_GetTicks()) % 5;
			// 2 points per square
		//Left Side
			roadVBOVECTOR.push_back((squareWidth * x)); //x  Move over twice the square width (since we're not sharing vertices)
			//roadVBOVECTOR.push_back(0.0f);
			roadVBOVECTOR.push_back(sin(y) + randSeed);
			roadVBOVECTOR.push_back(-1 * zValue);
			//Color
			//roadVBOVECTOR.push_back(redValue);
			roadVBOVECTOR.push_back(((float)((int)yValue % colorStep)) / colorStep);
			//	roadVBOVECTOR.push_back(greenValue);
			roadVBOVECTOR.push_back(((float)x) / ((float)gridWidth));
			roadVBOVECTOR.push_back(blueValue);


			//Right Side
			/*
			roadVBOVECTOR.push_back((squareWidth * (x + 1) * 2)); //x
			//roadVBOVECTOR.push_back(0.0f);
			roadVBOVECTOR.push_back(0.0f);
			roadVBOVECTOR.push_back(-1 * zValue);
			//Color
			//roadVBOVECTOR.push_back(redValue);
			roadVBOVECTOR.push_back(((float)((int)yValue % colorStep)) / colorStep);
			roadVBOVECTOR.push_back(((float)x) / ((float)gridLength));
			roadVBOVECTOR.push_back(blueValue);
			*/

			/*
					for (y = 0; y < (triangles); y++) {

						for (z = 0; z < 3; z++) { // 3 points in triangle
							// 4 Vertices for square, 6 indices
					//Left Side


							roadVBOVECTOR.push_back(-1); //x
							roadVBOVECTOR.push_back(0.5f);
							roadVBOVECTOR.push_back(zValue);
							//Color
							roadVBOVECTOR.push_back(redValue);
							roadVBOVECTOR.push_back(greenValue);
							roadVBOVECTOR.push_back(blueValue);
							//Right Side
							roadVBOVECTOR.push_back(1); //x
							roadVBOVECTOR.push_back(0.5f);
							roadVBOVECTOR.push_back(zValue);
							//Color
							roadVBOVECTOR.push_back(redValue);
							roadVBOVECTOR.push_back(greenValue * sin(((float)y) / 2));
							roadVBOVECTOR.push_back(blueValue);


							//Indices


							//roadIndices.push_back(y + z); // 4 need 2 more

						}
						// indices come in sets of 3
					}
					*/
		}
	}
	// Lets do our indices
	//vertices in row = gridLength *2
	/*
	for (GLuint j = 0; j < triangles; j++) {
		// for each triangle
		for (int k = 0; k < 3; k++) { // triangle has 3 points
			roadIndices.push_back(j + k);
		}
	}
	*/
	/*
		for (GLuint i = 0; i < gridWidth; i++) { // for each row
			for (GLuint j = 0; j < 2; j++) {// for each Row Block (when pattern repeats)

				//First row in Pattern
				for (GLuint k = 0; k < trianglesInRow; k++) { // for each triangle in a row
					for (GLuint l = 0; l < 3; l++) { // for each vertice in that triangle
						roadIndices.push_back(i + k + l);

					}

				//Second row in Pattern
					for (GLuint r = 0; r < trianglesInRow; k++) { // the second one with weird stuff
						for (GLuint s = 0; s < 3; s++) { // for each vertice in this row
							//bottom Left indice = ( 2 * current row) + 1;
							// top Left =
							roadIndices.push_back((i *))
						}

				}
				}
			}
		}
		*/
	//GLuint patternBlocks = gridWidth / 2; // This will only work if gridWidth is an even number
	GLuint pointsInRow = gridLength + 1;// points in single row (column)
	//bool rowO = true;
	for (GLuint i = 0; i < gridWidth; i++) { // for each row
	//	for (GLuint j = 0; j < 2; j++) {// for each Row Block (when pattern repeats)
		/*
		if (i % 2 != 0) { // if odd
			// Do the weird row stuff
			for (GLuint r = 0; r <= gridLength; r++) { // the second one with weird stuff


				// For each square
			//	int tCount = 0;

				// First Value = [ (row - 1) * (PointsInRow) / 2] + 1
				// Second Value = (PointsInRow - 1) + FirstValue
				GLuint FirstValue = ((i - 1) * pointsInRow / 2) + 1 + (2 * r); // 2 *r is what square you're at
				GLuint SecondValue = (FirstValue + pointsInRow - 1);
				GLuint ThirdValue = FirstValue + 2;
				GLuint FourthValue = SecondValue + 2;

				//First Triangle of Square
				roadIndices.push_back(FirstValue);
				roadIndices.push_back(SecondValue);
				roadIndices.push_back(ThirdValue);

				//Second Triangle of Square
				roadIndices.push_back(SecondValue);
				roadIndices.push_back(ThirdValue);
				roadIndices.push_back(FourthValue);
				/*
				roadIndices.push_back(1 + (i * 2 * pointsInRow) + r); // Bottom Left
				roadIndices.push_back(1 + (i * 2 * pointsInRow) + r + 3); //Bottom right
				roadIndices.push_back(1 + (i * 2 * pointsInRow) + r + 2);//top left
				*/


		//	}
		//}
		//*/
	//	else { // If normal
				//First row in Pattern Block
			for (GLuint k = 0; k < gridLength; k++) { // for each triangle in a row
				//for (GLuint l = 0; l < 3; l++) { // for each vertice in that triangle
				GLuint bottomLeftIndice = (i * pointsInRow) + k;
				GLuint bottomRightIndice = ( ( (i + 1) * pointsInRow ) + k);
				//GLuint topLeftIndice = (((i)*pointsInRow) + k + 3);
				GLuint topLeftIndice = bottomLeftIndice + 1;
				GLuint topRightIndice = bottomRightIndice + 1;
						//roadIndices.push_back(	(i * pointsInRow) + k ); // bottom left;
						//roadIndices.push_back(((i + 1) * pointsInRow) + k); // bottom right; (adjacent row)
					//	roadIndices.push_back(((i)* pointsInRow) + k + 3); // top left;
				//Triangle 1
						roadIndices.push_back(bottomLeftIndice); // bottom left;
						roadIndices.push_back(bottomRightIndice); // bottom right; (adjacent row)
						roadIndices.push_back(topLeftIndice); // top left;
				//Triangle 2
					 // bottom left;
						roadIndices.push_back(bottomRightIndice); // bottom right; (adjacent row)
						roadIndices.push_back(topLeftIndice); // top left;
						roadIndices.push_back(topRightIndice);
	
				//}
			}
		//}

		// We need to create the EBO

	// Actual Buffer Stuff;
		glGenBuffers(1, &this->roadVBO); // controls our vertice information
		glGenBuffers(1, &this->roadEBO); // tells us how to render the quads

	// GEN and BIND our VAO
		glGenVertexArrays(1, &this->roadVAO);
		glBindVertexArray(this->roadVAO);
		// Bind our VBO
		glBindBuffer(GL_ARRAY_BUFFER, this->roadVBO);
		glBufferData(GL_ARRAY_BUFFER, roadVBOVECTOR.size() * sizeof(GLfloat), roadVBOVECTOR.data(), GL_DYNAMIC_DRAW);
		// Bind our Index / Element stuff
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->roadEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->roadIndices.size() * sizeof(GLuint), roadIndices.data(), GL_DYNAMIC_DRAW);

		// VBO attributes (position and color)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
}

//Memory Leak Fix
void OpenGLManager::generateRoad5(GLuint gridWidth, GLuint gridLength, GLfloat squareWidth, GLfloat squareLength) {

	GLuint x, y, z;
	float redValue = 0.5f;
	float greenValue = 0.1f;
	float blueValue = 0.9f;
	GLuint triangles = gridWidth * gridLength * 2;
	GLuint trianglesInRow = gridLength * 2;
	//	int vertexCounter;
	GLuint initialZ = 0;
	GLfloat zStep = squareLength;
	GLuint colorStep = 100;
	// Lets create a square
	// indices = squares * 3;
	// Initial 2 points no matter what
	for (x = 0; x < gridWidth * 2; x++) {
		for (y = 0; y <= gridLength; y++) { // x = 0 is the initial 2 points
		//	float zValue = -1 * (x * 10);
			float zValue = initialZ + (zStep * y);
			float yValue = (sinf(y) * 10);
			float randSeed = (rand() * SDL_GetTicks()) % 5;
			// 2 points per square
		//Left Side
			//Position
			roadVBOVECTOR.push_back((squareWidth * x)); //x  Move over twice the square width (since we're not sharing vertices) X
			//roadVBOVECTOR.push_back(0.0f); // To make it flat grid;
			roadVBOVECTOR.push_back((sin(y + randSeed) * 2) + 4); // Y
			roadVBOVECTOR.push_back(-1 * zValue); //Z
			//Color
			//roadVBOVECTOR.push_back(redValue);
			roadVBOVECTOR.push_back(((float)((int)yValue % colorStep)) / colorStep);
			//	roadVBOVECTOR.push_back(greenValue);
			roadVBOVECTOR.push_back(x / gridWidth);
			roadVBOVECTOR.push_back(blueValue);


			//Right Side
			/*
			roadVBOVECTOR.push_back((squareWidth * (x + 1) * 2)); //x
			//roadVBOVECTOR.push_back(0.0f);
			roadVBOVECTOR.push_back(0.0f);
			roadVBOVECTOR.push_back(-1 * zValue);
			//Color
			//roadVBOVECTOR.push_back(redValue);
			roadVBOVECTOR.push_back(((float)((int)yValue % colorStep)) / colorStep);
			roadVBOVECTOR.push_back(((float)x) / ((float)gridLength));
			roadVBOVECTOR.push_back(blueValue);
			*/

			/*
					for (y = 0; y < (triangles); y++) {

						for (z = 0; z < 3; z++) { // 3 points in triangle
							// 4 Vertices for square, 6 indices
					//Left Side


							roadVBOVECTOR.push_back(-1); //x
							roadVBOVECTOR.push_back(0.5f);
							roadVBOVECTOR.push_back(zValue);
							//Color
							roadVBOVECTOR.push_back(redValue);
							roadVBOVECTOR.push_back(greenValue);
							roadVBOVECTOR.push_back(blueValue);
							//Right Side
							roadVBOVECTOR.push_back(1); //x
							roadVBOVECTOR.push_back(0.5f);
							roadVBOVECTOR.push_back(zValue);
							//Color
							roadVBOVECTOR.push_back(redValue);
							roadVBOVECTOR.push_back(greenValue * sin(((float)y) / 2));
							roadVBOVECTOR.push_back(blueValue);


							//Indices


							//roadIndices.push_back(y + z); // 4 need 2 more

						}
						// indices come in sets of 3
					}
					*/
		}
	}
	// Lets do our indices
	//vertices in row = gridLength *2
	/*
	for (GLuint j = 0; j < triangles; j++) {
		// for each triangle
		for (int k = 0; k < 3; k++) { // triangle has 3 points
			roadIndices.push_back(j + k);
		}
	}
	*/
	/*
		for (GLuint i = 0; i < gridWidth; i++) { // for each row
			for (GLuint j = 0; j < 2; j++) {// for each Row Block (when pattern repeats)

				//First row in Pattern
				for (GLuint k = 0; k < trianglesInRow; k++) { // for each triangle in a row
					for (GLuint l = 0; l < 3; l++) { // for each vertice in that triangle
						roadIndices.push_back(i + k + l);

					}

				//Second row in Pattern
					for (GLuint r = 0; r < trianglesInRow; k++) { // the second one with weird stuff
						for (GLuint s = 0; s < 3; s++) { // for each vertice in this row
							//bottom Left indice = ( 2 * current row) + 1;
							// top Left =
							roadIndices.push_back((i *))
						}

				}
				}
			}
		}
		*/
		//GLuint patternBlocks = gridWidth / 2; // This will only work if gridWidth is an even number
	GLuint pointsInRow = gridLength + 1;// points in single row (column)
	GLuint bottomLeftIndice, bottomRightIndice, topLeftIndice, topRightIndice;
	//bool rowO = true;
	for (GLuint i = 0; i < gridWidth; i++) { // for each row
	//	for (GLuint j = 0; j < 2; j++) {// for each Row Block (when pattern repeats)
		/*
		if (i % 2 != 0) { // if odd
			// Do the weird row stuff
			for (GLuint r = 0; r <= gridLength; r++) { // the second one with weird stuff


				// For each square
			//	int tCount = 0;

				// First Value = [ (row - 1) * (PointsInRow) / 2] + 1
				// Second Value = (PointsInRow - 1) + FirstValue
				GLuint FirstValue = ((i - 1) * pointsInRow / 2) + 1 + (2 * r); // 2 *r is what square you're at
				GLuint SecondValue = (FirstValue + pointsInRow - 1);
				GLuint ThirdValue = FirstValue + 2;
				GLuint FourthValue = SecondValue + 2;

				//First Triangle of Square
				roadIndices.push_back(FirstValue);
				roadIndices.push_back(SecondValue);
				roadIndices.push_back(ThirdValue);

				//Second Triangle of Square
				roadIndices.push_back(SecondValue);
				roadIndices.push_back(ThirdValue);
				roadIndices.push_back(FourthValue);
				/*
				roadIndices.push_back(1 + (i * 2 * pointsInRow) + r); // Bottom Left
				roadIndices.push_back(1 + (i * 2 * pointsInRow) + r + 3); //Bottom right
				roadIndices.push_back(1 + (i * 2 * pointsInRow) + r + 2);//top left
				*/


				//	}
				//}
				//*/
			//	else { // If normal
						//First row in Pattern Block
		for (GLuint k = 0; k < gridLength; k++) { // for each triangle in a row
			//for (GLuint l = 0; l < 3; l++) { // for each vertice in that triangle
			bottomLeftIndice = (i * pointsInRow) + k;
			bottomRightIndice = (((i + 1) * pointsInRow) + k);
			//GLuint topLeftIndice = (((i)*pointsInRow) + k + 3);
			topLeftIndice = bottomLeftIndice + 1;
			topRightIndice = bottomRightIndice + 1;
			//roadIndices.push_back(	(i * pointsInRow) + k ); // bottom left;
			//roadIndices.push_back(((i + 1) * pointsInRow) + k); // bottom right; (adjacent row)
		//	roadIndices.push_back(((i)* pointsInRow) + k + 3); // top left;
	//Triangle 1
			roadIndices.push_back(bottomLeftIndice); // bottom left;
			roadIndices.push_back(bottomRightIndice); // bottom right; (adjacent row)
			roadIndices.push_back(topLeftIndice); // top left;
	//Triangle 2
		 // bottom left;
			roadIndices.push_back(bottomRightIndice); // bottom right; (adjacent row)
			roadIndices.push_back(topLeftIndice); // top left;
			roadIndices.push_back(topRightIndice);

			//}
		}
		//}

		// We need to create the EBO

	// Actual Buffer Stuff;
		glGenBuffers(1, &this->roadVBO); // controls our vertice information
		glGenBuffers(1, &this->roadEBO); // tells us how to render the quads

	// GEN and BIND our VAO
		glGenVertexArrays(1, &this->roadVAO);
		glBindVertexArray(this->roadVAO);
		// Bind our VBO
		glBindBuffer(GL_ARRAY_BUFFER, this->roadVBO);
		glBufferData(GL_ARRAY_BUFFER, roadVBOVECTOR.size() * sizeof(GLfloat), roadVBOVECTOR.data(), GL_DYNAMIC_DRAW);
		// Bind our Index / Element stuff
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->roadEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->roadIndices.size() * sizeof(GLuint), roadIndices.data(), GL_DYNAMIC_DRAW);

		// VBO attributes (position and color)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
}


void OpenGLManager::renderRoad() {
	if (this->movingShader == nullptr) {
		this->shaderInitSuccess = false;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TraingleShader init fail", "couldn't make it", NULL);
	}
	else {
		//Matrices
		glm::mat4 transformMatrice = glm::mat4(1.0f);
	//	transformMatrice = glm::translate(transformMatrice, glm::vec3(0.5, 0.5f, 0.0f));
	//	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); // projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		//	glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	
		// note that we're translating the scene in the reverse direction of where we want to move
		
		//////////
		movingShader->use();

		//GLfloat r = 0.5f;
	//	GLfloat g = 0.5f;
	//	GLfloat b = 0.5f;

		glUniformMatrix4fv(msTransform->location, 1, GL_FALSE, glm::value_ptr(transformMatrice)); // set pos
		glUniformMatrix4fv(msView, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(msProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(msView, 1, GL_FALSE, glm::value_ptr(ortho));


		//glUniform4f(msColor->location, r, g, b, 1.0f);

		//triangleShader->use();
		//frameRate = SDL_GetTicks() - this->timeValue;
		glBindVertexArray(this->roadVAO);


		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawElements(GL_TRIANGLES, this->roadIndices.size(), GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(glWindow);



	}
}

// Mountain Shader Renderer
void OpenGLManager::renderRoad2() {
	if (this->mountainShader == nullptr) {
		this->shaderInitSuccess = false;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TraingleShader init fail", "couldn't make it", NULL);
	}
	else {
		//Matrices
		
		//	transformMatrice = glm::translate(transformMatrice, glm::vec3(0.5, 0.5f, 0.0f));
		//	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); // projection matrix
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		//	glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

		// note that we're translating the scene in the reverse direction of where we want to move

		//////////
		mountainShader->use();

		GLfloat r = 0.5f;
		GLfloat g = 0.5f;
		GLfloat b = 0.5f;

		glUniformMatrix4fv(mountTransform->location, 1, GL_FALSE, glm::value_ptr(transformMatrice)); // set pos
		glUniformMatrix4fv(mountView, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(mountProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(msView, 1, GL_FALSE, glm::value_ptr(ortho));


		//glUniform4f(msColor->location, r, g, b, 1.0f);

		//triangleShader->use();
		//frameRate = SDL_GetTicks() - this->timeValue;
		glBindVertexArray(this->roadVAO);


		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawElements(GL_TRIANGLES, this->roadIndices.size(), GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(glWindow);



	}
}

// Render Road 2 but using new camera Object for View
void OpenGLManager::renderRoad3() {
	if (this->mountainShader == nullptr) {
		this->shaderInitSuccess = false;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TraingleShader init fail", "couldn't make it", NULL);
	}
	else {
		//Matrices

		//	transformMatrice = glm::translate(transformMatrice, glm::vec3(0.5, 0.5f, 0.0f));
		//	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); // projection matrix
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		//	glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

		// note that we're translating the scene in the reverse direction of where we want to move

		//////////
		mountainShader->use();

		GLfloat r = 0.5f;
		GLfloat g = 0.5f;
		GLfloat b = 0.5f;

		glUniformMatrix4fv(mountTransform->location, 1, GL_FALSE, glm::value_ptr(transformMatrice)); // set pos
		glUniformMatrix4fv(mountView, 1, GL_FALSE, glm::value_ptr(this->gameCamera->getView()));
		glUniformMatrix4fv(mountProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(msView, 1, GL_FALSE, glm::value_ptr(ortho));


		//glUniform4f(msColor->location, r, g, b, 1.0f);

		//triangleShader->use();
		//frameRate = SDL_GetTicks() - this->timeValue;
		glBindVertexArray(this->roadVAO);


		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // WIREFRAME MODE

		glDrawElements(GL_TRIANGLES, this->roadIndices.size(), GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(glWindow);



	}
}


void OpenGLManager::updateCameraView(glm::vec3 translation) {
	this->view = glm::translate(this->view, translation);

}

void OpenGLManager::updateCameraView2(direction moveDirection) {
	this->gameCamera->moveCamera(moveDirection);

}


void OpenGLManager::rotateCameraView2(direction directions) {
	
	//this->view = glm::rotate(this->view, glm::radians(angle), vecAxis);
	this->gameCamera->rotateCamera(directions);
}

// Resolution of road (how many quads), Distance, End Points (xF, yF)
		// LERP between Xi and Xf and Yi and Yf

