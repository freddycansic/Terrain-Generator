#include "Cube.h"
#include <glad/glad.h>
#include "Utils.h"

Cube::Cube(float size, vector<float> pos) {
	vector<GLfloat> vertices;
	//vertices = Utils::join(vertices, pos);													 // bottom front left
	//vertices = Utils::join(vertices, vector<float>{ pos[0] + size, pos[1], pos[2] });		 // bottom front right
	//vertices = Utils::join(vertices, vector<float>{ pos[0], pos[1], pos[2] - size });        // bottom back left
	//vertices = Utils::join(vertices, vector<float>{ pos[0] - size, pos[1], pos[2] - size }); // bottom back right

	//vertices = Utils::join(vertices, vector<float>{ pos[0], pos[1] + size, pos[2] });				// top front left
	//vertices = Utils::join(vertices, vector<float>{ pos[0] + size, pos[1] + size, pos[2] });		// top front right
	//vertices = Utils::join(vertices, vector<float>{ pos[0], pos[1] + size, pos[2] - size });		// top back left
	//vertices = Utils::join(vertices, vector<float>{ pos[0] - size, pos[1] + size, pos[2] - size }); // top back right
	this->vertices = vertices;
}