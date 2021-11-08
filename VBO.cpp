#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // sizeof = size of data in bytes, GL_STATIC_DRAW means it will be modified once and then drawn
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID); // points functions to vbo
}

void VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO() {
	glDeleteBuffers(1, &ID);
}