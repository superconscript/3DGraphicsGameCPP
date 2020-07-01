#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
//	glewInit();
	bool init = glewInitialize();
	if (init != true) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Shader Glew Constr", "GLEW INIT FAIL", NULL);
	}
	else {
		std::string vertexCode; // what we'll store the vertex and fragment code in, (from the files)
		std::string fragmentCode;
		//this->gEngine = gEngine;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// lets open the files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close the files
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (std::ifstream::failure e)
		{
			//std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl; // need to change this to work with SDL (simple msg box)
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ShaderFileReading", "Couldn't read shader files", NULL);
		}
		// If everything worked lets convert it so OpenGL can use it
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// Noe we need to compile Everything
		GLuint vertex, fragment;
		int success;
		char infoLog[512];

		// Compiling vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl; // Convert to SDL simple msg box
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "VERTEX_COMPILATION_FAILED", infoLog, NULL); // done
		}
		else {
			// Fragment Shader Compilation
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);
			if (!success) {
				int* log = 0;
				glGetShaderInfoLog(fragment, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl; // need to convert
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FRAGMENT_COMPILATION_FAILED", infoLog, NULL);
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, log);
				std::string logString = std::to_string(*log);
				const char* log2 = logString.c_str();
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FRAGMENT_COMPILATION_FAILED", log2 , NULL);
			}
			else { // Everything compiled good, lets link them
				this->ID = glCreateProgram();
				glAttachShader(ID, vertex);
				glAttachShader(ID, fragment);
				glLinkProgram(ID);

				glGetProgramiv(ID, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(ID, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl; // need to convert
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LINKING_FAILED", infoLog, NULL);
				}
				else { // Linking Succesful
					glDeleteShader(vertex); // delete now that they're linked
					glDeleteShader(fragment);
				}
			}
		}
	}
}
bool Shader::glewInitialize() {
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Shader glewInit Failure", "glew init failure", NULL);
		return false;
	}
	else {
		return true;
	}
}
void Shader::use() {
	//glewInit();
	if (this == nullptr) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Shader::USE", "this is nullptr", NULL);
	}
	else {
		glUseProgram(this->ID);
	}
//	gEngine->useShader(ID);
	//bool initSuccess = glewInitialize();
	//if (initSuccess) {
	//	glUseProgram(this->ID); // we'll change this to a call to game Engine to use it
	//}
	//else {
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Shader use glew fail", "GLEW INIT FAILURE SHADER USE", NULL);
	//}
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);

}// const after means "this" pointer is const
void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

UniformHolder::UniformHolder(GLuint shaderID, GLuint location) {
	this->shaderID = shaderID;
	this->location = location;

}

/*
BufferHolder::BufferHolder(GLuint ID, void* dataArray, int size) {
	this->arraySize = size;
	this->dataArray = dataArray;
	this->ID = ID;
}
BufferHolder::BufferHolder(GLuint ID, GLfloat dataArray, int size) : type{ "GLfloat" } {
	this->arraySize = size;
	this->dataArray = dataArray;
	this->ID = ID;
}// unknown
BufferHolder::BufferHolder(GLuint ID, GLuint dataArray, int size) : type{ "GLuint" } {
	this->arraySize = size;
	this->dataArray = dataArray;
	this->ID = ID;

}
*/