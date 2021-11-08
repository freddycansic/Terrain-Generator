#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

Window::Window(const unsigned int height, const unsigned int width, const char* title) {
	this->height = height;
	this->width = width;
	this->title = title;
}

void Window::create() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use modern opengl functions

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (window == NULL) {
		glfwTerminate();
		throw std::runtime_error("GLFW window did not initialise.");
	}
	glfwMakeContextCurrent(window); // introduce window into current context
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::update() {
	glfwSwapBuffers(window); // swap front and back buffer
	glfwPollEvents(); // check for events
}

Window::~Window() {
	glfwTerminate();
	glfwDestroyWindow(window);
}