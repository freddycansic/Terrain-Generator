#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <glad/glad.h>
#include "Utils.h"

using std::vector;

class Cube {

public:
	Cube(float size, float pos[3], float coords[2]);

private:
	vector<float> vertices;
	vector<unsigned int> indices;

};

#endif
