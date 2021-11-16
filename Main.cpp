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



int main() {
	// Mesh declaration
	vector<Mesh> meshes;

	for (int i = -50; i < 50; i++) {
		for (int k = -50; k < 50; k++) {
			meshes.push_back(*(new Cube(0.5f, i / 2, k / 2, 0.0f)));
		}
	}

	assert(meshes.size());
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

	assert(allVecIndices.size()); // check that threads returned something
	assert(allVecVertices.size());

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

	// configure opengl
	glEnable(GL_DEPTH_TEST); // dont draw triangles that are behind other triangles

	while (!window.shouldClose()) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // clear back buffer with black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.activate();
		tex.bind();

		// camera
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // position = world origin = -3 on z axis (positive 3 because z axis increases as you move away from the screen)
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // target = world origin
		glm::vec3 cameraDirection = glm::vec3(glm::normalize(cameraPos - cameraTarget)); // subtracting vectors = difference between them (learnopengl 8.4)

		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // literally have no idea what this does
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); // or this
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); // or this

		glm::mat4 model = glm::mat4(1.0f); // initialise identity matrices
		glm::mat4 proj = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		// transform object
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f)); // vec3 = axis to rotate on

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f)); // moves camera away from object by 2 units and down 1/2 units
		proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 1.0f, 1000.0f); // fov, aspect ratio, closest clipping point, furthest clipping point. basically render distance

		// uniforms
		GLuint modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // 1 = num of matrices, false = dont do weird matrix maths shit, valueptr = get pointer to matrix instead of actual matrix data

		GLuint viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLuint projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		VAO1.bind();

		// Draw
		glDrawElements(GL_TRIANGLES, (GLsizei) allVecIndices.size(), GL_UNSIGNED_INT, 0); // 0 = starting index, 6 = num of vertices to be used (6 = 3 (triangle) * 2))

		window.update();
	} 

	delete[] allIndices;
	delete[] allVertices;

	return 0;
}