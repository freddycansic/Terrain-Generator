#include "Texture.h"

Texture::Texture(const char* filePath) {
	data = stbi_load(filePath, &width, &height, &nbrChannels, 0);

	glGenTextures(1, &ID); // 1 = how many textures are being calculated
	glBindTexture(GL_TEXTURE_2D, ID); // bind texture so that following commands will be executed on current texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // repeat texture on x axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // repeat texture on y axis

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // on minifying texture use nearest filtering 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // same on magnifying

	if (data) {   
		glTexImage2D(GL_TEXTURE_2D, // target
					0, // mipmap level (no mipmap)
					GL_RGBA, // data channels (can be GL_RGBA)
					width, height, 
					0, // no idea 
					GL_RGB, GL_UNSIGNED_BYTE, // type of data being entered, byte because char = 8bit
					data);

		glGenerateMipmap(GL_TEXTURE_2D); // generate mipmaps
	}
	else {
		std::cout << "Texture failed to load." << std::endl;
	}

	stbi_image_free(data);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}