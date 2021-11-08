#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID); // 1 = number of 3d shapes
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset); // 0 = the attribute is position, 3 = number of floats per position (x, y, z), data type, ignore, stride = offset between data pieces, index of first data
	glEnableVertexAttribArray(layout); // layout = the attribute index
	VBO.unbind();
}

void VAO::bind() {
	glBindVertexArray(ID);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &ID); // cleans up all
}