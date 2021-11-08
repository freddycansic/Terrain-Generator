#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glad/glad.h>
#include <iostream>
#include "Utils.h"

using std::vector;

class Mesh
{
public:
	void printVertices();

	vector<GLfloat> getVertices();
	vector<GLuint> getIndices();

	void setVertices(vector<GLfloat> vertices);
	void setIndices(vector<GLuint> indices);

	static vector<GLfloat> compileAllVertices(vector<Mesh> meshes) {

		vector<GLfloat> allVertices = {};

		for (Mesh mesh : meshes) { // for every mesh
			// at the end of allVertices, append the next set of vertices from mesh[i]
		//	vector::iter
			allVertices = Utils::join(allVertices, mesh.getVertices());
			//allVertices.insert(allVertices.end(), mesh.getVertices().begin(), mesh.getVertices().end()); // WEIRD ERROR
		}

		return allVertices;
	}

	static vector<GLuint> compileAllIndices(vector<Mesh> meshes) {
		
		vector<GLuint> indices;
		unsigned int lastIndex = 0;

		for (Mesh mesh : meshes) {
			indices = Utils::join(indices, mesh.getIndices()); // compile all indices into 1 vec
		}

		for (int i = 0; i < indices.size(); i++) {
			indices[i] = indices[i] + lastIndex; // increment every index by whatever the last index was
		}

		return indices;

	}

private:
	vector<GLfloat> vertices;
	vector<GLuint> indices;
};

#endif

