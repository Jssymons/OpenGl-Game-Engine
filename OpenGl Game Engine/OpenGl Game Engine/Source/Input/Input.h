#pragma once
#include <GL\glfw3.h>
#include <glm\vec2.hpp>

class Input
{
public:
	static void SetWindow(GLFWwindow* displayWindow);
	static void Update();
	static bool GetKey(int keyCode);
	static bool GetKeyDown(int keyCode);
	static bool GetKeyUp(int keyCode);
	static glm::vec2 GetMousePos();
	static bool GetMouse(int mouseButton);
	static bool GetMouseUp(int mouseButton);
	static bool GetMouseDown(int mouseButton);
	static const int NUM_KEYCODES = 256;
	static const int NUM_MOUSECODES = 7;
private:
	static void UpdateMouse();
	static GLFWwindow* window;
	static glm::vec2 mousePosition;
	static bool currentKeys[NUM_KEYCODES];
	static bool downKeys[NUM_KEYCODES];
	static bool upKeys[NUM_KEYCODES];
	static bool currentMouse[NUM_MOUSECODES];
	static bool downMouse[NUM_MOUSECODES];
	static bool upMouse[NUM_MOUSECODES];
};

