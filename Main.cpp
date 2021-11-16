#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>
#include <cstdlib>
#include <thread>

#include "Shader.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "Window.h"
#include "Texture.h"
#include "Cube.h"
#include "Utils.h"
#include "Camera.h"
#include "Mesh.h"

using std::cout;
using std::endl;
using namespace Globals;

//	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // 0 pyramid
//	-0.5f, -0.5f, 0.5f,  1.0f, 0.0f,  // 1
//	0.5f, -0.5f, 0.5f,   0.0f, 1.0f,  // 2
//	0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // 3
//	0.0f, 0.7f, 0.0f,    1.0f, 1.0f,  // 4
//
//  0, 1, 2,  // pyramid
//	0, 2, 3,
//	0, 1, 4,
//	1, 2, 4,
//	2, 3, 4,
//	3, 0, 4,
//

glm::vec3 cubePos[] = {
	
	glm::vec3(1.0f, 0.3f, 0.4f),
	glm::vec3(0.1f, 0.4f, 0.1f),
	glm::vec3(0.2f, 0.1f, 0.3f),
	glm::vec3(0.3f, 0.5f, 0.25f),
	glm::vec3(0.5f, 0.7f, 0.6f),
	glm::vec3(0.8f, 0.5f, 0.75f),
	glm::vec3(0.3f, 0.3f, 0.25f),
	glm::vec3(0.7f, 0.2f, 0.65f),
	glm::vec3(0.3f, 0.5f, 0.25f),

};

int main() {
	// Mesh declaration
	vector<Mesh> meshes;

	for (float i = -5; i < 5; i++) {
		for (float k = -5; k < 5; k++) {
			for (float j = -5; j < 5; j++) {
				meshes.push_back(*(new Cube(0.5f, i, k, j)));
			}
		}
	}

	//***************************************************************************************************
	const auto start = std::chrono::system_clock::now();

	vector<GLfloat> allVecVertices;// = Mesh::compileAllVertices(meshes);
	
	//Compile vertices on a separate thread
	std::thread t1([&allVecVertices, meshes]() mutable {
		allVecVertices = Mesh::compileAllVertices(meshes);
	});

	// Compile indices on a separate thread
	vector<GLuint> allVecIndices;
	std::thread t2([&allVecIndices, meshes]() mutable {
		allVecIndices = Mesh::compileAllIndices(meshes);
	});
	
	t1.join(); // wait for both threads to finish
	t2.join();

	//vector<GLfloat> allVecVertices = Mesh::compileAllVertices(meshes);
	//vector<GLuint> allVecIndices = Mesh::compileAllIndices(meshes);

	GLfloat* allVertices = new GLfloat[allVecVertices.size()]; // arr on heap because array size needs to be "dynamic"
	for (unsigned int i = 0; i < allVecVertices.size(); i++) { // for every in allglvertices
		allVertices[i] = allVecVertices[i];
	}

	GLuint* allIndices = new GLuint[allVecIndices.size()];
	for (unsigned int i = 0; i < allVecIndices.size(); i++) {
		allIndices[i] = allVecIndices[i];
	}

	auto end = std::chrono::system_clock::now();
	std::cout << "Compiling took: " << (float) ((end - start) / 10000000.0f).count() << "s" << std::endl;

	//assert(allVecIndices.size()); // check that threads returned something
	//assert(allVecVertices.size());

	//Utils::printVertices(allVecVertices);
	//Utils::printIndices(allVecIndices);

	//Utils::printArr(allVertices, allVecVertices.size());
	//Utils::printArr(allIndices, allVecIndices.size());

	//***************************************************************************************************

	Window window(WIDTH, HEIGHT, "Help me");
	window.create();

	gladLoadGL(); // configure opengl with glad
	glViewport(0, 0, WIDTH, HEIGHT); // sets view to 0-900 width, 0-900 height

	Shader shaderProgram("default.vert", "default.frag"); // wraps vertex and frag shaders into program

	VAO VAO1;

	// Binding and adding data to buffers
	VAO1.bind();

	VBO VBO1(allVertices, sizeof(GLfloat) * allVecVertices.size());
	EBO EBO1(allIndices, sizeof(GLuint) * allVecIndices.size());

	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0); // links position to layout
	VAO1.linkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float))); // links texture coords to layout

	// unbind to not accidentally modify
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	// initialise texture
	Texture tex("uvTest.jpg", GL_TEXTURE_2D, GL_NEAREST, GL_NEAREST, GL_REPEAT);

	// initialise camera
	Camera camera;

	// configure opengl
	glEnable(GL_DEPTH_TEST); // dont draw triangles that are behind other triangles

	while (!window.shouldClose()) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // clear back buffer with black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.activate();
		tex.bind();

		camera.update(shaderProgram.ID, window.getWindow());

		VAO1.bind();

		// Draw
		glDrawElements(GL_TRIANGLES, (GLsizei) allVecIndices.size(), GL_UNSIGNED_INT, 0); // 0 = starting index, 6 = num of vertices to be used (6 = 3 (triangle) * 2))

		window.update();
	} 

	delete[] allIndices;
	delete[] allVertices;

	return 0;
}