#include "Texture.h"

const char* Texture::imgType() {
	std::string fileStr(filePath);
	int indexdot = fileStr.find(".");
	return (fileStr.substr(indexdot + 1, fileStr.size() - indexdot)).c_str();
}

Texture::Texture(const char* filePath, GLenum target, GLuint magFiltering, GLuint minFiltering, GLuint texWrap) {
	this->target = target;
	this->filePath = filePath;
	data = stbi_load(filePath, &width, &height, &nbrChannels, 0);

	glGenTextures(1, &ID); // 1 = how many textures are being calculated
	glBindTexture(target, ID); // bind texture so that following commands will be executed on current texture

	glTexParameteri(target, GL_TEXTURE_WRAP_S, texWrap); // repeat texture on x axis

	if(target == GL_TEXTURE_2D || target == GL_TEXTURE_3D) // if using 2d or 3d texture
		glTexParameteri(target, GL_TEXTURE_WRAP_T, texWrap); // repeat texture on y axis

	if (target == GL_TEXTURE_3D) // if using 3d texture
		glTexParameteri(target, GL_TEXTURE_WRAP_T, texWrap); // repeat texture on z axis

	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFiltering); // on minifying texture use nearest filtering 
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFiltering); // same on magnifying

	if (data) {   
		if (imgType() == "png" || imgType() == "bmp") {
			glTexImage2D(target, // target
				0, // mipmap level (no mipmap)
				GL_RGBA, // data channels (can be GL_RGB)
				width, height,
				0, // no idea 
				GL_RGBA, GL_UNSIGNED_BYTE, // type of data being entered, byte because char = 8bit
				data);
		}
		else {
			glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // if not png or bmp then dont use alpha channel
		}
		
		glGenerateMipmap(target); // generate mipmaps
	}
	else {
		std::cout << "Texture failed to load." << std::endl;
	}

	stbi_image_free(data);
}

void Texture::bind() {
	glBindTexture(target, ID);
}

void Texture::unbind() {
	glBindTexture(target, 0);
}