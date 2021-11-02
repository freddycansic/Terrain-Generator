#ifndef TEXTURE_H
#define TEXTURE_H
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>

class Texture {

public:
	Texture(const char* filePath);
	void bind();
	void unbind();

private:
	int width, height, nbrChannels;
	unsigned char* data;
	unsigned int ID;
};

#endif