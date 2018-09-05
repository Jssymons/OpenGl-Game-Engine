#include "Input.h"

GLFWwindow* Input::window;
bool Input::currentKeys[Input::NUM_KEYCODES];
bool Input::downKeys[Input::NUM_KEYCODES];
bool Input::upKeys[Input::NUM_KEYCODES];
bool Input::currentMouse[NUM_MOUSECODES];
bool Input::downMouse[NUM_MOUSECODES];
bool Input::upMouse[NUM_MOUSECODES];
glm::vec2 Input::mousePosition(0, 0);

void Input::Update()
{
	for (int i = 0; i < NUM_KEYCODES; i++)
	{
		bool pressed = GetKey(i);
		upKeys[i] = !pressed && currentKeys[i];
		downKeys[i] = pressed && !currentKeys[i];
		currentKeys[i] = pressed;
	}

	for (int i = 0; i < NUM_MOUSECODES; i++)
	{
		bool pressed = GetMouse(i);
		upMouse[i] = !pressed && currentMouse[i];
		downMouse[i] = pressed && !currentMouse[i];
		currentMouse[i] = pressed;
	}

	UpdateMouse();
}

bool Input::GetKey(int keyCode)
{
	return (glfwGetKey(window, keyCode) == GLFW_PRESS);
}

bool Input::GetKeyDown(int keyCode)
{
	return downKeys[keyCode];
}

bool Input::GetKeyUp(int keyCode)
{
  	return upKeys[keyCode];
}

glm::vec2 Input::GetMousePos()
{
	return mousePosition;
}

bool Input::GetMouse(int mouseCode)
{
	return (glfwGetMouseButton(window, mouseCode) == GLFW_PRESS);
}

bool Input::GetMouseDown(int mouseCode)
{
	return downMouse[mouseCode];
}

bool Input::GetMouseUp(int mouseCode)
{
	return upMouse[mouseCode];
}

void Input::UpdateMouse()
{
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	mousePosition.x = x;
	mousePosition.y = y;
}

void Input::SetWindow(GLFWwindow* displayWindow)
{
	window = displayWindow;
}