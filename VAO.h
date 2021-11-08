#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {

public:
	GLuint ID;
	VAO();
	~VAO();
					// buffer object, index of attrib in array, num of components per vertex, data type of component, distance to next set of data, offset from index 0 to the first data entry
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();
};

#endif
