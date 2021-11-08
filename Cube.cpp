#include "Cube.h"

Cube::Cube(GLfloat size, GLfloat x, GLfloat y, GLfloat z) {
	vector<GLfloat> vertices; // empty vector where vertices will be stored

	vertices = Utils::join(vertices, vector<GLfloat>{ x, y, z,					    0.0f, 0.0f} ); // bottom front left
    vertices = Utils::join(vertices, vector<GLfloat>{ x + size, y, z,			    1.0f, 0.0f} ); // bottom front right
	vertices = Utils::join(vertices, vector<GLfloat>{ x, y, z - size,			    1.0f, 1.0f} ); // bottom back left
	vertices = Utils::join(vertices, vector<GLfloat>{ x - size, y, z - size,		0.0f, 0.0f} ); // bottom back right

	vertices = Utils::join(vertices, vector<GLfloat>{ x, y + size, z,			    0.0f, 0.0f} ); // top front left
	vertices = Utils::join(vertices, vector<GLfloat>{ x + size, y + size, z,	    1.0f, 1.0f} ); // top front right
	vertices = Utils::join(vertices, vector<GLfloat>{ x, y + size, z - size,		0.0f, 0.0f} ); // top back left
	vertices = Utils::join(vertices, vector<GLfloat>{ x - size, y + size, z - size, 1.0f, 1.0f} ); // top back right
	
	setVertices(vertices);

	setIndices(vector<GLuint> {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		0, 1, 4,
		1, 4, 5,
		3, 2, 7,
		2, 7, 6,
		1, 2, 6,
		1, 6, 2,
		0, 3, 4,
		3, 4, 7
	});
}