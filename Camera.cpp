#include "Camera.h"

void Camera::update(GLuint shaderProgramID, GLFWwindow* window) {
	model = mat4(1.0f); // initialise identity matrices
	proj = mat4(1.0f);
	view = mat4(1.0f);

	cameraPos = vec3(0.0f, 0.0f, 3.0f); // position = world origin = -3 on z axis (positive 3 because z axis increases as you move away from the screen)
	cameraFront = vec3(0.0f, 0.0f, -1.0f);
	cameraUp = vec3(0.0f, 1.0f, 0.0f);

	view = translate(view, vec3(0.0f, 0.0f, -2.0f)); // moves camera away from object by 2 units and down 1/2 units
	proj = perspective(radians(45.0f), (float)WIDTH / HEIGHT, 1.0f, 1000.0f); // fov, aspect ratio, closest clipping point, furthest clipping point. basically render distance

	view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	GLuint modelLoc = glGetUniformLocation(shaderProgramID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model)); // 1 = num of matrices, false = dont do weird matrix maths shit, valueptr = get pointer to matrix instead of actual matrix data

	GLuint viewLoc = glGetUniformLocation(shaderProgramID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

	GLuint projLoc = glGetUniformLocation(shaderProgramID, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
}

void Camera::processMovement(GLFWwindow* window) {

	const float cameraSpeed = 0.05f; // idfkkkkkkk
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}
