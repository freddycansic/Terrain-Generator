#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "Window.h"
#include "Texture.h"
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::endl;

const unsigned int WIDTH = 800, HEIGHT = 800;

GLfloat red = 0.0f, green = 0.0f, blue = 0.0f;

// Vertices coordinates
GLfloat vertices[] =
{ //     coords                colors        texCoords
	//-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,   // back left bottom   0 cube
	//-0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,   // front left bottom  1
	//0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,   // front right bottom 2
	//0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,   // back right bottom  3
	//-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // back left top       4
	//-0.5f, 0.5f, 0.5f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // front left top      5
	//0.5f, 0.5f, 0.5f,    1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // front right top     6
	//0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 0.0f,  1.0f, 0.0f   // back right top      7 
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 0
	-0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 1
	0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f, 0.0f, 1.0f,   // 2
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // 3
	0.0f, 0.7f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f, 1.0f     // 4
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

float randf(float max) {
	return (float(rand()) / float((RAND_MAX)) * max);
}

void randomiseColors(GLfloat* vertices) {
	int size = (int) sizeof(vertices) / sizeof(vertices[0]);
	float randFloat;

	for (int i = 3; i < size; i += 6) { // for each vertex (initial rgb = 3(offset), i+=6 = each vertex)
		for (int k = i; k < i + 3; k++) { // for each r g b
			randFloat = randf(0.02f);
			//rtices[k] + randFloat >= 1.0f ? vertices[k] = 0;
			cout << randf(0.02f) << endl;
		}
	}

}

int main() {
	srand((unsigned int)time(0));

	Window window(WIDTH, HEIGHT, "Pong");

	window.create();

	gladLoadGL(); // configure opengl with glad
	glViewport(0, 0, WIDTH, HEIGHT); // sets view to 0-900 width, 0-900 height

	Shader shaderProgram("default.vert", "default.frag"); // wraps vertex and frag shaders into program

	VAO VAO1;

	// Binding and adding data to buffers
	VAO1.bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); // links position to layout
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // links color to layout
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // links texture coords to layout

	Texture tex("cube.png");

	// unbind
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// configure opengl
	glEnable(GL_DEPTH_TEST); // dont draw triangles that are behind other triangles
	//glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LESS);
	glDepthRange(0.1, 100);
	//glFrontFace(GL_CW);
	

	while (!window.shouldClose()) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // clear back buffer with black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//blue < 1.0f ? blue += (float(rand()) / float((RAND_MAX)) * 0.02f) : blue = 0;
		//red < 1.0f ? red += (float(rand()) / float((RAND_MAX)) * 0.02f) : red = 0;
		//green < 1.0f ? green += (float(rand()) / float((RAND_MAX)) * 0.02f) : green = 0;

		shaderProgram.activate();
		tex.bind();

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += 0.01f;
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f); // initialise identity matrices
		glm::mat4 proj = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate on y=1
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f)); // moves camera away from object by 2 units and down 1/2 units
		proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f); // fov, aspect ratio, closest clipping point, furthest clipping point. basically render distance

		GLuint modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // 1 = num of matrices, false = dont do weird matrix maths shit, valueptr = get pointer to matrix instead of actual matrix data

		GLuint viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLuint projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));



		VAO1.bind();

		// Draw
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0); // 0 = starting index, 6 = num of vertices to be used (6 = 3 (triangle) * 2))

		window.update();
	}

	tex.unbind();
	VAO1.destroy();
	EBO1.destroy();
	VBO1.destroy();
	shaderProgram.destroy();
	window.destroy();

	return 0;
}