#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <string>

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
#include "CubeMapTexture.h"

const unsigned int WIDTH = 1920;
const unsigned int HEIGHT = 1080;
const unsigned int VERTEX_LENGTH = 6;

using std::cout;
using std::endl;

int main() {
	const auto start = std::chrono::system_clock::now(); // start benchmark

	// Mesh declaration
	vector<Mesh> staticMeshes;
	
	unsigned int resolution = 5;
	unsigned int permutations = 10;
	float maxHeight = 2.5f;

	vector<GLfloat> allCubeYPos = Utils::noiseGenerator(permutations, resolution, maxHeight);
	staticMeshes.reserve(allCubeYPos.size());

	print("Compiling begun.");
	//Utils::printVec(allCubeYPos);
	
	float cubeSize = 1.0f;
	unsigned int rowLength = (permutations - 1) * resolution + 1;

	for (int i = 0; i < rowLength * rowLength; i+=rowLength) {
		for (int k = i, j = 0; k < i + rowLength && j < rowLength; k++, j++) {
			//std::cout << k << " ";

			staticMeshes.emplace_back(Cube(cubeSize, i / rowLength, allCubeYPos[k], j));
		}
		//std::cout << std::endl;
	}

	//***************************************************************************************************
	
	//Compile vertices on a separate thread
	vector<GLfloat> allVecVertices;
	std::thread t1([&allVecVertices, staticMeshes]() mutable {
		allVecVertices = Mesh::compileAllVertices(staticMeshes);
	});

	// Compile indices on a separate thread
	vector<GLuint> allVecIndices;
	std::thread t2([&allVecIndices, staticMeshes]() mutable {
		allVecIndices = Mesh::compileAllIndices(staticMeshes);
	});
	
	t1.join(); // wait for both threads to finish
	t2.join();

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

	gladLoadGL(); // configure opengl with glad
	glViewport(0, 0, WIDTH, HEIGHT); // sets view to 0-900 width, 0-900 height

	Shader shaderProgram("default.vert", "default.frag"); // wraps vertex and frag shaders into program

	VAO VAO1;

	// Binding and adding data to buffers
	VAO1.bind();

	VBO VBO1(allVertices, sizeof(GLfloat) * allVecVertices.size());
	EBO EBO1(allIndices, sizeof(GLuint) * allVecIndices.size());

	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, VERTEX_LENGTH * sizeof(float), (void*)0); // links position to layout
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, VERTEX_LENGTH * sizeof(float), (void*)(3 * sizeof(float))); // links texture coords to layout

	// unbind to not accidentally modify
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	// initialise texture
	//Texture tex("uvTest.jpg", GL_TEXTURE_2D, GL_NEAREST, GL_NEAREST, GL_REPEAT);
	vector<string> filePaths = { "grass_side.jpg","grass_side.jpg", // left right side
								 "grass_top.jpg","grass_bottom.jpg", // top bottom
								 "grass_side.jpg","grass_side.jpg" }; // front back
	CubeMapTexture cubeMap(filePaths, GL_NEAREST, GL_NEAREST);

	// initialise camera
	Camera camera(window.getWindow());

	// configure opengl
	glEnable(GL_DEPTH_TEST); // dont draw triangles that are behind other triangles
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	while (!window.shouldClose()) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // clear back buffer with color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.activate();
		//tex.bind();
		cubeMap.bind();

		camera.update(shaderProgram.ID, window.getWindow()); // recalculates matrices and handles movement

		VAO1.bind();

		glDrawElements(GL_TRIANGLES, (GLsizei)allVecIndices.size(), GL_UNSIGNED_INT, 0); // 0 = starting index, 6 = num of vertices to be used (6 = 3 (triangle) * 2))

		// Draw
		//std::thread t3([allVecIndices, allIndices]() {
		//	glDrawRangeElements(GL_TRIANGLES, 0, allIndices[allVecIndices.size() / 2], allVecIndices.size() / 2,
		//		GL_UNSIGNED_INT, 0);
		//});

		//t3.join();

		window.update();
	} 

	delete[] allIndices;
	delete[] allVertices;

	return 0;
}