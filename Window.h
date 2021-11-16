#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window {

public:
	Window(const unsigned int height, const unsigned int width, const char* title);
	~Window();

	void create();
	bool shouldClose();
	void update();

	GLFWwindow* getWindow();

private:
	GLFWwindow* window;
	unsigned int height;
	unsigned int width;
	const char* title;
	void processInput(GLFWwindow* window);
};

#endif