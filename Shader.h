#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string getFileContents(const char* fileName);

class Shader {

public:
	GLuint ID; // reference
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void activate();
};

#endif
