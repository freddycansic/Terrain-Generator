#include "Camera.h"

extern const unsigned int WIDTH;
extern const unsigned int HEIGHT;

// position = world origin = -3 on z axis (positive 3 because z axis increases as you move away from the screen)
vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

double deltaTime = 0.0f;
double lastFrame = 0.0f;
double currentFrame = 0.0f;

double yaw = -90.0, pitch = 0.0, lastX = 0.0, lastY = 0.0; // yaw = -90 to counteract random camera movement on first frame
bool firstMouse = true;

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	//double negativeYPos = yPos * -1; // invert movement so that moving mouse up moves camera up

	if (firstMouse) // update last pos to current pos on first frame
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	double xOffset = xPos - lastX;
	double yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	const float sensitivity = 0.1f;
	xOffset *= sensitivity; // scale down magnitude of mouse movements
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) pitch = 89.0f; // limit user to only be able to look directly up at the skybox
	if (pitch < -89.0f) pitch = -89.0f; // same but only can look down as far as their feet

	glm::vec3 direction;
	direction.x = cos(glm::radians((float)yaw)) * cos(glm::radians((float)pitch));
	direction.y = sin(glm::radians((float)pitch));
	direction.z = sin(glm::radians((float)yaw)) * cos(glm::radians((float)pitch));
	cameraFront = glm::normalize(direction);
}

Camera::Camera(GLFWwindow* window) {
	glfwSetCursorPosCallback(window, mouseCallback);
}

void Camera::update(GLuint shaderProgramID, GLFWwindow* window) {
	currentFrame = glfwGetTime(); // calculate deltatime
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	view = mat4(1.0f);
	model = mat4(1.0f); // initialise identity matrices
	proj = mat4(1.0f);

	proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 1.0f, 1000.0f); // fov, aspect ratio, closest clipping point, furthest clipping point. basically render distance

	view = translate(view, vec3(0.0f, 0.0f, -2.0f)); // moves camera away from object by 2 units and down 1/2 units
	
	processKeyInput(window);

	// recalculate view matrix every frame and sent it to vert shader with uniform
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	GLuint viewLoc = glGetUniformLocation(shaderProgramID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLuint modelLoc = glGetUniformLocation(shaderProgramID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // 1 = num of matrices, false = dont do weird matrix maths stuff, valueptr = get pointer to matrix instead of actual matrix data

	GLuint projLoc = glGetUniformLocation(shaderProgramID, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

}

void Camera::processKeyInput(GLFWwindow* window) {
	float cameraSpeed = 2.5f * (float) deltaTime; // deltatime = time taken for last frame to render
	
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { // sprinting
		cameraSpeed *= 2;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; // no clue what this means
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}
