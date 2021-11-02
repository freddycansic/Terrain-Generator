#ifndef TEXTURE_H
#define TEXTURE_H
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>
#include <string>

class Texture {

public:
	Texture(const char* filePath, GLenum target, GLuint magFiltering, GLuint minFiltering, GLuint texWrap);
	void bind();
	void unbind();

private:
	int width, height, nbrChannels;
	unsigned char* data;
	unsigned int ID;
	const char* filePath;
	const char* imgType();
	GLenum target;
};

#endif