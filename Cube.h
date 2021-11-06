#ifndef CUBE_H
#define CUBE_H

#include <vector>

using std::vector;

class Cube {

public:
	Cube(float size, vector<float> pos);

private:
	vector<float> vertices;
	vector<unsigned int> indices;

};

#endif
