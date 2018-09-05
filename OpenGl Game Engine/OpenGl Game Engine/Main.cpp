#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GL/glfw3.h>
#include <Application\Application.h>


int main(int argv, char* argc) {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	Application application;

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	application.Start();
}