#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils.h"

using namespace Globals;

Window::Window(const unsigned int height, const unsigned int width, const char* title) {
	this->height = height;
	this->width = width;
	this->title = title;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use modern opengl functions

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

	window = glfwCreateWindow(vidmode->width, vidmode->height, title, NULL, NULL);

	if (window == NULL) {
		glfwTerminate();
		throw std::runtime_error("GLFW window did not initialise.");
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // "captures" cursor meaning it is hidden and stays in the middle of the screen
	
	glfwMakeContextCurrent(window); // introduce window into current context
}

//void Window::setCursorPosCallback(GLFWcursorposfun func) {
//	glfwSetCursorPosCallback(window, func); // set callback functions
//}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void Window::update() {
	processInput(window);
	glfwSwapBuffers(window); // swap front and back buffer
	glfwPollEvents(); // check for events
}

Window::~Window() {
	glfwTerminate();
	glfwDestroyWindow(window);
}

GLFWwindow* Window::getWindow() {
	return window;
}