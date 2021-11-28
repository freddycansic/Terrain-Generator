#include "CubeMapTexture.h"

CubeMapTexture::CubeMapTexture(vector<string> filePaths, GLenum magFiltering, GLenum minFiltering) {
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	assert(filePaths.size() == 6);

	unsigned int startingFace = GL_TEXTURE_CUBE_MAP_POSITIVE_X; // learnopengl 27.1
	for (unsigned int i = 0; i < filePaths.size(); i++) // 6 iterations because 6 faces on cube
	{
		data = stbi_load(filePaths[i].c_str(), &width, &height, &nbrChannels, 0); // populate width height nbrChannels

		if (!data) throw std::invalid_argument("Image data failed to load.");

		glTexImage2D(startingFace + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magFiltering);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFiltering);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // 3 dimensions
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


}

CubeMapTexture::~CubeMapTexture() {
	unbind();
}

void CubeMapTexture::bind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void CubeMapTexture::unbind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}