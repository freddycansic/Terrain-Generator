#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <glad/glad.h>
#include "Utils.h"
#include <iostream>

using std::vector;

class Cube {

public:
	Cube(float size, vector<float> pos);

	vector<float> getVertices();
	vector<unsigned int> getIndices();
	void printVertices();

private:
	vector<float> vertices;
	vector<unsigned int> indices;

};

#endif
