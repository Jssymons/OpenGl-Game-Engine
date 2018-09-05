#pragma once
#include <GL\glfw3.h>
#include <string>

class Display
{
	public:
		Display();
		GLFWwindow* CreateWindow(int width, int height, std::string title);
		void Render();
		void Dispose();
		bool WindowShouldClose();
		bool CheckKeyPress(int key);
		int GetWidth();
		int GetHeight();
		GLFWwindow* GetWindow();
private:
	GLFWwindow* window;
	int windowWidth;
	int windowHeight;
};

