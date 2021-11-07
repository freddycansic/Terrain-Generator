#include "Cube.h"

Cube::Cube(GLfloat size, vector<GLfloat> pos) {
	vector<GLfloat> vertices;
	vertices = Utils::join(vertices, vector<GLfloat>{ pos[0], pos[1], pos[2],						 0.0f, 0.0f} ); // bottom front left
	vertices = Utils::join(vertices, vector<GLfloat>{ pos[0] + size, pos[1], pos[2],				 0.0f, 0.0f} ); // bottom front right
	std::cout << pos[0] + size << std::endl;
	vertices = Utils::join(vertices, vector<GLfloat>{ pos[0], pos[1], pos[2] - size,				 0.0f, 0.0f} ); // bottom back left
	vertices = Utils::join(vertices, vector<GLfloat>{ pos[0] - size, pos[1], pos[2] - size,		 0.0f, 0.0f} ); // bottom back right

	vertices = Utils::join(vertices, vector<GLfloat>{ pos[0], pos[1] + size, pos[2],				 0.0f, 0.0f} ); // top front left
	vertices = Utils::join(vertices, vector<GLfloat>{ pos[0] + size, pos[1] + size, pos[2],		 1.0f, 1.0f} ); // top front right
	vertices = Utils::join(vertices, vector<GLfloat>{ pos[0], pos[1] + size, pos[2] - size,		 0.0f, 0.0f} ); // top back left
	vertices = Utils::join(vertices, vector<GLfloat>{ pos[0] - size, pos[1] + size, pos[2] - size, 0.0f, 0.0f} ); // top back right
	this->vertices = vertices;
}

vector<float> Cube::getVertices() {
	return this->vertices;
}

vector<unsigned int> Cube::getIndices() {
	return this->indices;
}

void Cube::printVertices() {
	for (int i = 0; i < this->getVertices().size() / 5; i++) { // 6 = 3 position coords + 2 texture coords
		for (int k = 0; k < 5; k++) {
			std::cout << this->getVertices()[k] << ((k==2) ? "  " : " "); // after pos coords do an extra space to show where the texture coords are also take any chance to use a ternary operator cause its so fucking cool
		}
		std::cout << std::endl;
	}
}