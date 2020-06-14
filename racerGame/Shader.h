#pragma once
//#include 
#include <GL/glew.h>
#include <gl\GLU.h>
#include <string>
#include <iostream> // Ill remove this once I implement SDL simple msg boxes for error reporting;
#include <fstream>
#include <sstream>
#include <SDL.h> // For error msg boxs when creating shaders
class Shader {
public:
	GLuint ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};