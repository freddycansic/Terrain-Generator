#include "CubeMapTexture.h"

CubeMapTexture::CubeMapTexture(const char* filePath) {
	data = stbi_load(filePath, &width, &height, &nbrChannels, 0);

	glGenTextures(1, &ID);
}
