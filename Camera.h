#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Utils.h"
#include <GLFW/glfw3.h>

using namespace Globals;
using namespace glm;

class Camera {

public:
	
	void update(GLuint shaderProgramID, GLFWwindow* window);

private:

	void processMovement(GLFWwindow* window);

	GLuint shaderProgramID;
	GLFWwindow* window;

	mat4 model;
	mat4 proj;
	mat4 view;

	vec3 cameraPos;
	vec3 cameraFront;
	vec3 cameraUp;
};

#endif