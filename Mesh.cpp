#include "Mesh.h"

//unsigned int VERTEX_LENGTH = 8;
extern const unsigned int VERTEX_LENGTH;

void Mesh::printVertices() {
	for (int i = 0; i < this->getVertices().size() / VERTEX_LENGTH; i++) { // 5 = 3 position coords + 2 texture coords
		for (int k = 0; k < VERTEX_LENGTH; k++) {
			std::cout << this->getVertices()[i * VERTEX_LENGTH + k] << ((k == 2) ? "  " : " "); // after pos coords do an extra space to show where the texture coords are also take any chance to use a ternary operator cause its so cool
		}
		std::cout << std::endl;
	}
}

vector<GLfloat> Mesh::getVertices() {
	return this->vertices;
}

vector<GLuint> Mesh::getIndices() {
	return this->indices;
}

void Mesh::setIndices(const vector<GLuint> &indices) {
	this->indices = indices;
}

void Mesh::setVertices(const vector<GLfloat> &vertices) {
	this->vertices = vertices;
}