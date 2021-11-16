#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <iostream>
#include "Utils.h"

class Mesh
{
	public:
		void printVertices();

		vector<GLfloat> getVertices();
		vector<GLuint> getIndices();

		void setVertices(const vector<GLfloat> &vertices);
		void setIndices(const vector<GLuint> &indices);

		static vector<GLfloat> compileAllVertices(const vector<Mesh> &meshes) {

			vector<GLfloat> allVertices = {};

			for (Mesh mesh : meshes) { // for every mesh
				// at the end of allVertices, append the next set of vertices from mesh[i]
			//	vector::iter
				allVertices = Utils::join(allVertices, mesh.getVertices());
				//allVertices.insert(allVertices.end(), mesh.getVertices().begin(), mesh.getVertices().end()); // WEIRD ERROR
			}

			return allVertices;
		}

		static vector<GLuint> compileAllIndices(const vector<Mesh> &meshes) {
		
			vector<GLuint> indices;
			unsigned int lastMaxIndex = 0;

			for (Mesh mesh : meshes) {
				vector<GLuint> nextIndices = mesh.getIndices();
				nextIndices = Utils::incrementAll(nextIndices, lastMaxIndex);
				indices = Utils::join(indices, nextIndices); // compile all indices into 1 vec

				lastMaxIndex = Utils::maxInVec(mesh.getIndices()) + lastMaxIndex + 1; // get max from last indices
			}

			return indices;
		}

	private:
		vector<GLfloat> vertices;
		vector<GLuint> indices;
};

#endif

