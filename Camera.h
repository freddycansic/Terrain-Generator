#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Utils.h"
#include <GLFW/glfw3.h>

using namespace Globals;
using glm::mat4;
using glm::vec3;

class Camera {

public:
	
	Camera(GLFWwindow* window);
	void update(GLuint shaderProgramID, GLFWwindow* window);

private:

	void processKeyInput(GLFWwindow* window);

	GLuint shaderProgramID;
	GLFWwindow* window;

	mat4 model;
	mat4 proj;
	mat4 view;
};

#endif