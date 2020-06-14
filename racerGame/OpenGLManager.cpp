#include "OpenGLManager.h"
#include "Shader.h"

Shader* triangleShader;
OpenGLManager::OpenGLManager(SDL_Window* glWindow, gameEngine* gameEngine ) {
	glewInitialize();
	this->glWindow = glWindow;
	this->gEngine = gameEngine;
	initShaders();
}
OpenGLManager::~OpenGLManager() {

}

void OpenGLManager::initShaders() {
	Shader* triangleShader = this->gEngine->createShader("shaders/shader.vs", "shaders/shader.fs");
}

bool OpenGLManager::RenderSomething(SDL_Window* glWindow) {
	return success;
}



	void OpenGLManager::renderTriangle(GLuint VAO, GLuint VBO, GLuint gProgramID) {
		triangleShader->use();
	//frameRate = SDL_GetTicks() - this->timeValue;
		float timeDiff = SDL_GetTicks();
		float greenValue = sin(timeDiff / 500) / 2.0f + 0.5f;
		float redValue = (sin(timeDiff / 2.0f) + .9f);
		
		

	//	glUseProgram(gProgramID);
	//	int vertexColorLocation = glGetUniformLocation(gProgramID, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SDL_GL_SwapWindow(glWindow);
	//	counter++;
		this->timeValue = SDL_GetTicks() / 1000;
		
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
