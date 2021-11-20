#include "Cube.h"

Cube::Cube(GLfloat size, GLfloat x, GLfloat y, GLfloat z) {
	vector<GLfloat> vertices; // empty vector where vertices will be stored

	GLfloat halfSize = size / 2;

	vertices = Utils::join(vertices, array<GLfloat, 6>{ x - halfSize, y - halfSize, z - halfSize, -0.5f, -0.5f, -0.5f}); // bottom front left
    vertices = Utils::join(vertices, array<GLfloat, 6>{ x + halfSize, y - halfSize, z - halfSize, 0.5f, -0.5f, -0.5f} ); // bottom front right
	vertices = Utils::join(vertices, array<GLfloat, 6>{ x + halfSize, y - halfSize, z + halfSize, 0.5f, -0.5f, 0.5f} ); // bottom back right
	vertices = Utils::join(vertices, array<GLfloat, 6>{ x - halfSize, y - halfSize, z + halfSize, -0.5f, -0.5f, 0.5f} ); // bottom back left
									 
	vertices = Utils::join(vertices, array<GLfloat, 6>{ x - halfSize, y + halfSize, z - halfSize, -0.5f, 0.5f, -0.5f} ); // top front left
	vertices = Utils::join(vertices, array<GLfloat, 6>{ x + halfSize, y + halfSize, z - halfSize, 0.5f, 0.5f, -0.5f} ); // top front right
	vertices = Utils::join(vertices, array<GLfloat, 6>{ x + halfSize, y + halfSize, z + halfSize, 0.5f, 0.5f, 0.5f} ); // top back right
	vertices = Utils::join(vertices, array<GLfloat, 6>{ x - halfSize, y + halfSize, z + halfSize, -0.5f, 0.5f, 0.5f} ); // top back left
	
	setVertices(vertices);

	setIndices(vector<GLuint> {
		2, 0, 1,
		3, 0, 2,
		6, 4, 5,
		7, 4, 6,
		7, 3, 6,
		6, 3, 2,
		4, 0, 5,
		5, 0, 1,
		7, 3, 4,
		4, 3, 0,
		6, 2, 5,
		5, 2, 1
	});
}