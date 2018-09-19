#include "Display.h"
#include <string>

Display::Display()
{
}

GLFWwindow* Display::CreateWindow(int width, int height, std::string title)
{
	// Create the window with the given width, height and title
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	// Check in the window was created successfully
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
	}

	// Configure the window
	glfwMakeContextCurrent(window);										// Make the created window the current context
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);				// Window input mode
	glfwSwapInterval(0);												// Vsync (0 = off, 1 = on)
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);		// Set mouse cursor settings
	glfwSetCursorPos(window, width / 2, height / 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);						// OpenGl major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						// OpenGl minor version
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// OpenGl compatability mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// OpenGl profile

	// Store the width & height
	windowWidth = width;
	windowHeight = height;

	return window;
}

void Display::Render()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Display::WindowShouldClose()
{
	return glfwWindowShouldClose(window) == 0;
}

bool Display::CheckKeyPress(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

int Display::GetWidth()
{
	return windowWidth;
}

int Display::GetHeight()
{
	return windowHeight;
}

void Display::Dispose()
{
	glfwDestroyWindow(window);
}

GLFWwindow* Display::GetWindow()
{
	return window;
}