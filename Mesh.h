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

	vector<float> getVertices();
	vector<unsigned int> getIndices();

	void setVertices(vector<GLfloat> vertices);
	void setIndices(vector<unsigned int> indices);

	static vector<GLfloat> compileAllVertices(vector<Mesh> meshes) {
		unsigned int numVerts = 0;

		for (int i = 0; i < meshes.size(); i++) {
			numVerts += meshes[i].getVertices().size();
		}

		vector<GLfloat> allVertices;

		for (int i = 0; i < meshes.size(); i++) { // for every mesh
			// at the end of allVertices, append the next set of vertices from mesh[i]
			allVertices.insert(allVertices.end(), meshes[i].getVertices().begin(), meshes[i].getVertices().end());
		}

		return allVertices;
	}

	static vector<unsigned int> compileAllIndices(vector<Mesh> meshes) {
		
		vector<unsigned int> indices;
		unsigned int lastIndex = 0;

		for (Mesh mesh : meshes) {
			for (int i = 0; i < mesh.getIndices().size() / 3; i++) { // /3 because triangle

			}

			indices = Utils::join(indices, mesh.getIndices());
		}

	}

private:
	vector<GLfloat> vertices;
	vector<unsigned int> indices;
};

#endif

