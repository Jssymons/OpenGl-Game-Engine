#include "Input.h"
#include "../World/Blocks/Block.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\ext.hpp>

GLFWwindow* Input::window;
bool Input::currentKeys[Input::NUM_KEYCODES];
bool Input::downKeys[Input::NUM_KEYCODES];
bool Input::upKeys[Input::NUM_KEYCODES];
bool Input::currentMouse[NUM_MOUSECODES];
bool Input::downMouse[NUM_MOUSECODES];
bool Input::upMouse[NUM_MOUSECODES];
const float Input::mouseX = Globals::SCREEN_WIDTH / 2;
const float Input::mouseY = Globals::SCREEN_HEIGHT / 2;
glm::vec3 Input::mouseDirection(0, 0, 0);
Block* Input::currentBlock;

void Input::Update(Camera* camera, World* world)
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

	UpdateMouse(camera, world);
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

glm::vec3 Input::GetMouseDirection()
{
	return mouseDirection;
}

Block* Input::GetCurrentBlock()
{
	return currentBlock;
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

void Input::SetWindow(GLFWwindow* displayWindow)
{
	window = displayWindow;
}


void Input::UpdateMouse(Camera* camera, World* world)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	RotateCamera(camera, x, y);
	glfwSetCursorPos(window, mouseX, mouseY);

	mouseDirection = CalculateMouseRay(camera);

	auto block = GetSelectedBlock(mouseDirection, world, camera);

	if (block)
	{
		currentBlock = block;
	}
}

void Input::RotateCamera(Camera* camera, double x, double y)
{
	glm::vec3 currentRotation = camera->GetRotation();
	currentRotation.y += (x - mouseX) * 0.25;
	currentRotation.x += (y - mouseY) * 0.25;

	if (currentRotation.x > 80) {
		currentRotation.x = 80;
	}
	else if (currentRotation.x < -80)
	{
		currentRotation.x = -80;
	}

	if (currentRotation.y < 0) {
		currentRotation.y = 360;
	}
	else if (currentRotation.y > 360)
	{
		currentRotation.y = 0;
	}

	camera->SetRotation(currentRotation);
}

glm::vec3 Input::CalculateMouseRay(Camera* camera)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	float normalizedMouseX = mouseX / (Globals::SCREEN_WIDTH  * 0.5f) - 1.0f;
	float normalizedMouseY = mouseY / (Globals::SCREEN_HEIGHT * 0.5f) - 1.0f;

	glm::vec4 screenPos = glm::vec4(normalizedMouseX, -normalizedMouseY, 0.0f, 0.0f);
	glm::mat4 inverseProjection = glm::inverse(camera->GetProjectionMatrix());
	glm::vec4 eyeCoords = inverseProjection * screenPos;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	glm::mat4 inverseView = glm::inverse(camera->GetViewMatrix());
	glm::vec4 worldRay = inverseView * eyeCoords;
	glm::vec3 dir = glm::normalize(glm::vec3(worldRay));

	return dir;
}

Block* Input::GetSelectedBlock(glm::vec3 ray, World* world, Camera* camera)
{
	glm::vec3 cameraPos = camera->GetPosition()/2;
	for (float i = 1.0f; i < Globals::RAY_RANGE; i += Globals::RAY_STEP)
	{
		glm::vec3 extension = ray * i;
		glm::vec3 position = cameraPos + extension;
		Block* block = world->GetBlockAt(position);
		if (block)
		{
			if (block->IsVisible()) {
				return block;
			}
		}
	}

	return nullptr;
}