#ifndef CUBE_MAP_TEXTURE_H
#define CUBE_MAP_TEXTURE_H

#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class CubeMapTexture
{
public:
	~CubeMapTexture();
	CubeMapTexture(vector<string> filePaths, GLenum magFiltering, GLenum minFiltering);
	void bind();
	void unbind();

private:
	int width;
	int height;
	int nbrChannels;
	unsigned char*data;
	unsigned int ID;
	GLenum target;
};

#endif