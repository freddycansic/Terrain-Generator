#ifndef CUBE_H
#define CUBE_H

#include "Mesh.h"
#include <array>

using std::array;
using std::vector;

class Cube : public Mesh{

public:
	Cube(GLfloat cubeSize, GLfloat x, GLfloat y, GLfloat z);
};

#endif
