#ifndef CUBE_H
#define CUBE_H

#include "Mesh.h"

using std::vector;

class Cube : public Mesh{

public:
	Cube(float cubeSize, GLfloat x, GLfloat y, GLfloat z);
};

#endif
