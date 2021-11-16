#ifndef CUBE_MAP_TEXTURE_H
#define CUBE_MAP_TEXTURE_H

#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>
#include <string>

class CubeMapTexture
{
public:
	CubeMapTexture(const char* filePath);

private:
	int width;
	int height;
	int nbrChannels;
	unsigned char*data;
	unsigned int ID;
	GLenum target;
};

#endif