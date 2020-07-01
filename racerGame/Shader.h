#pragma once
//#include 
#include <GL/glew.h>
#include <gl\GLU.h>
#include <string>
#include <iostream> // Ill remove this once I implement SDL simple msg boxes for error reporting;
#include <fstream>
#include <sstream>
#include <SDL.h> // For error msg boxs when creating shaders
//#include "gameEngine.h"
//class gameEngine;
struct UniformHolder {
	UniformHolder(GLuint shaderID, GLuint uniformLocation);
	~UniformHolder();

	GLuint location;
	GLuint shaderID;
};
/*
// Basic Buffer Holder (Father Struct)
struct BufferHolder { // unknown type
	BufferHolder(GLuint ID, int size); {this->ID = ID; this->arraySize = size; }
	
	int arraySize = 0; // to avoid out of bounds just in case
	GLuint ID;
	//void* dataArray[];
	//const char* type;
	bool alreadyConfigured = false; // for vertex attributes etc.
};

struct BufferHolderf : BufferHolder {
	BufferHolderf(GLuint ID, GLfloat* dataArray1, int size)
		: BufferHolder(ID, size) 
		, dataVector{ std::vector<GLfloat> vec(dataArray1, size) }; // initialize data array
		
		

	std::vector<GLfloat> dataVector;

};
// VBO buffer holder
struct BufferHolderVBO {// VBO basic class
	BufferHolderVBO(GLuint assignedVAO) { this->assignedVAO = assignedVAO; }
	bool active = false;
	GLuint assignedVAO;
};
	//GLFLoat	VBO Buffer
struct BufferHolderVBOf : BufferHolderf : BufferHolderVBO {
	BufferHolderVBOf(GLuint ID, GLfloat* dataArray, int size, GLuint assignedVAO) // Deferred to the Basic VBO
		: BufferHolderVBO(ID, dataArray, size, assignedVAO);
	GLfloat* dataArray[];

	};
	//GLuint
	


// Basic EBO buffer Holder
struct BufferHolderEBO : BufferHolder {
	bool active;
	GLuint assignedVAO;
	GLuint assignedVBO;
};

*/

class Shader {
public:
	GLuint ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	bool glewInitialize();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
private:
	//gameEngine* gEngine;
};

