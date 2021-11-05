#include "Cube.h"

Cube::Cube(float size, float pos[3], float textureCoords[2]) {
	vector<GLfloat> vertices;
	vector<float> vecPos = Utils::arrToVec(pos, 3);
	for (int i = 0; i < 8; i++) { // 8 vertices on cube
		vertices = Utils::join(vertices, vecPos);
	}

}