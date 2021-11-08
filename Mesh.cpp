#include "Mesh.h"

void Mesh::printVertices() {
	for (int i = 0; i < this->getVertices().size() / 5; i++) { // 5 = 3 position coords + 2 texture coords
		for (int k = 0; k < 5; k++) {
			std::cout << this->getVertices()[i * 5 + k] << ((k == 2) ? "  " : " "); // after pos coords do an extra space to show where the texture coords are also take any chance to use a ternary operator cause its so fucking cool
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